// LICENSE/*{{{*/
/*
  sxc - Simple Xmpp Client
  Copyright (C) 2008 Dennis Felsing, Andreas Waidler

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/*}}}*/

// INCLUDES/*{{{*/

#include <string>
#include <fstream>
#include <pthread.h>
#include <signal.h>

#include <libsxc/Exception/Type.hxx>

#include <cerrno>
#include <sstream>
#include <sys/stat.h>
#include <File/InputBase.hxx>
#include <Exception/FileInputException.hxx>
#include <Exception/Errno.hxx>

/*}}}*/

File::InputBase::InputBase()/*{{{*/
: _isFifoValid(false),
  _isListening(false),
  _mustClose(false)
{
}

/*}}}*/
File::InputBase::~InputBase()/*{{{*/
{
    close();
}

/*}}}*/
void File::InputBase::initialize(bool notPhysical)/*{{{*/
{
    _path = _createPath();

    if (!notPhysical) {
        try {
            validate();
        } catch (Exception::FileInputException &e) {
            // If the file is missing, create it. Anything else means that
            // someone tampered with the file.
            if (libsxc::Exception::FileMissing != e.getType())
                throw e;
            create();
        }
    }
}

/*}}}*/
void File::InputBase::create()/*{{{*/
{
    // Try to create FIFO with chmod 600.
    if (0 == mkfifo(_path.c_str(), S_IRUSR | S_IWUSR))
        return;

    // Creation of FIFO failed.
    libsxc::Exception::Type type = Exception::errnoToType(errno);
    std::string message  = "Could not create FIFO " + _path;
    throw Exception::FileInputException(type, message);
}

/*}}}*/
void File::InputBase::validate()/*{{{*/
{
    // Try to get file stats, needed for analyzing the chmod of the file.
    struct stat fstat;
    if (0 != stat(_path.c_str(), &fstat)) {
        libsxc::Exception::Type type = Exception::errnoToType(errno);
        std::string message  = "Could not get FIFO fstat: " + _path;
        throw Exception::FileInputException(type, message);
    }

    // Is this really a FIFO?
    if (!S_ISFIFO(fstat.st_mode)) {
        std::string message  = "Not a FIFO: " + _path;
        throw Exception::FileInputException(
            libsxc::Exception::BadFile,
            message);
    }

    // Check for chmod 600:
    if (0 == fstat.st_mode & S_IRUSR
    || 0 == fstat.st_mode & S_IWUSR
    || 0 != fstat.st_mode & S_IRGRP
    || 0 != fstat.st_mode & S_IWGRP
    || 0 != fstat.st_mode & S_IROTH
    || 0 != fstat.st_mode & S_IWOTH) {
        // Converts __mode_t st_mode to human-readable string (octal notation):
        std::stringstream mode;
        mode << std::oct << fstat.st_mode;
        // Extract only necessary part (user, group, other) from file mode:
        std::string message = _path + ": Chmod should be 600, found "
                            + mode.str().substr(2);
        throw Exception::FileInputException(
            libsxc::Exception::BadFile,
            message);
    }

    _isFifoValid = true;
}

/*}}}*/
void File::InputBase::read()/*{{{*/
{
    _fifo.open(_path.c_str());

    // See docblock of close().
    if (_mustClose)
        return;

    std::string lineBuffer;
    std::string input; // Filled with lineBuffer until other end closes the pipe
    while (getline(_fifo, lineBuffer)) {
        input += lineBuffer;
    }

    _handleInput(input);

    _fifo.close();
}

/*}}}*/
void File::InputBase::listen(bool blocking)/*{{{*/
{
    // Prevent input from being handled twice:
    if (_isListening) {
        std::string message = "Already listening on " + _path;
        throw Exception::FileInputException(
            libsxc::Exception::FileLocked,
            message);
    }
    _isListening = true;

    // Start the thread in the background.
    pthread_create(&_thread, NULL, _listen, this);
    // Join the thread when this functions should read in a blocking way.
    if (true == blocking)
        pthread_join(_thread, NULL);
}

/*}}}*/
void File::InputBase::close()/*{{{*/
{
    if (_isListening) {
        _mustClose = true;
        // Open an close FIFO in order to unblock subthread.
        std::ofstream out(_path.c_str());
        out.close();
        pthread_join(_thread, NULL);
    }

    _mustClose   = false;
    _isListening = false;
}

/*}}}*/
void *File::InputBase::_listen(void *fifo)/*{{{*/
{
    // FIXME: Add exception handling.
    InputBase *that = (InputBase *) fifo;
    do {
        // read() reads blocking until the other end closes the pipe. This 
        // loop will always restart read() after it handled some input and 
        // returned.
        that->read();
    } while (!that->_mustClose);

    that->_isListening = false;

    return NULL;
}

/*}}}*/

// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker

