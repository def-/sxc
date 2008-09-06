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

#ifdef HAVE_CONFIG_H
#   include <config.hxx>
#   include <print.hxx>
#endif

#include <cerrno>
#include <sys/stat.h>
#include <pthread.h>
#include <signal.h>

#include <list>
#include <string>
#include <fstream>
#include <sstream>

#include <File/AbcInput.hxx>
#include <Exception/FileInputException.hxx>
#include <Exception/Errno.hxx>
#include <libsxc/Exception/Type.hxx>

/*}}}*/

File::AbcInput::AbcInput()/*{{{*/
: _isFifoValid(false),
  _isListening(false),
  _mustClose(false)
{
}

/*}}}*/
File::AbcInput::~AbcInput()/*{{{*/
{
    if (_isListening)
        close();
}

/*}}}*/
void File::AbcInput::initialize(bool notPhysical)/*{{{*/
{
    _path = _createPath();

    if (!notPhysical) {
        try {
            _validate();
        } catch (Exception::FileInputException &e) {
            // If the file is missing, create it. Anything else means that someone
            // tampered with the file.
            if (libsxc::Exception::FileMissing != e.getType())
                throw e;
            _create();
        }
    }
}

/*}}}*/
void File::AbcInput::_create()/*{{{*/
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
void File::AbcInput::_validate()/*{{{*/
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
        throw Exception::FileInputException(libsxc::Exception::BadFile, message);
    }

    // Check for chmod 600(octal):
    int chmod = fstat.st_mode
              & (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    int chmodExpected = (S_IRUSR | S_IWUSR);
#ifdef DEBUG
    std::stringstream msg;
    msg << "fstat.st_mode = " << std::oct << fstat.st_mode << '\n';
    msg << "chmod         = " << std::oct << chmod         << '\n';
    msg << "expected      = " << std::oct << chmodExpected << '\n';
    printLog(msg.str());
#endif
    if (chmod != chmodExpected) {
        std::stringstream msg;
        msg << "Bad chmod: " << std::oct << chmod;
        // FIXME: Exceptions have to accept parameter being a string.
        std::string message = msg.str();
        throw Exception::FileInputException(libsxc::Exception::BadFile,
                                            message);
    }

    _isFifoValid = true;
}

/*}}}*/
std::string File::AbcInput::_read()/*{{{*/
{
    std::string input;
    std::string buf;

    _fifo.open(_path.c_str());
    while (!_fifo.eof()) {
        getline(_fifo, buf);
        input.append(buf);
        input.push_back('\n');
    }
    _fifo.close();

    input.erase(--input.end());

    return input;
}

/*}}}*/
void File::AbcInput::listen(bool blocking)/*{{{*/
{
    // Prevent input from being handled twice:
    if (_isListening) {
        std::string message = "Already listening on " + _path;
        throw Exception::FileInputException(libsxc::Exception::FileLocked, message);
    }
    _isListening = true;

#ifdef DEBUG
    printLog("Creating thread.");
#endif

    // Start the thread in the background.
    pthread_create(&_thread, NULL, _listen, (void*)this);

#ifdef DEBUG
    printLog("Thread created.");
#endif

    // Join the thread when this functions should read in a blocking way.
    if (true == blocking)
        pthread_join(_thread, NULL);

#ifdef DEBUG
    printLog("listen() ends here.");
#endif
}

/*}}}*/
void File::AbcInput::close()/*{{{*/
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
std::list<std::string> File::AbcInput::split(
    const std::string &data, const char delim)/*{{{*/
{
    std::istringstream in(data);
    std::string buf;
    std::list<std::string> splitted;

    do {
        getline(in, buf, delim);
        if (!buf.empty())
            splitted.push_back(buf);
    } while (!in.eof());

    return splitted;
}

/*}}}*/
void *File::AbcInput::_listen(void *fifo)/*{{{*/
{
#ifdef DEBUG
    printLog("Thread running.");
#endif
    // FIXME: Add exception handling. || called methods must not throw
    AbcInput *that = (AbcInput *) fifo;
    while (!that->_mustClose) {
        std::string input = that->_read();

        if (that->_mustClose) break;
        if (input.empty()) continue;

        std::list<std::string> inputs = AbcInput::split(input, '\0');
        for (std::list<std::string>::iterator it = inputs.begin();
             it != inputs.end();
             ++it)
        {
            that->_handleInput(*it);
        }
    }

#ifdef DEBUG
    printLog("Thread terminating.");
#endif

    return NULL;
}

/*}}}*/

// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
