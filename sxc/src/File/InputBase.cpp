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

/* $Id$ */

// INCLUDES/*{{{*/

#include <string>
#include <fstream>
#include <pthread.h>

#include <errno.h>
#include <sstream>
#include <sys/stat.h>
#include "InputBase.h"
#include "../Exception/FileInputException.h"
#include "../Exception/Errno.h"
#include "../Exception/Type.h"

/*}}}*/


File::InputBase::InputBase()/*{{{*/
: _isFifoValid(false),
  _isThreadRunning(false)
{
}

/*}}}*/
File::InputBase::~InputBase()/*{{{*/
{
    close();
}

/*}}}*/
void File::InputBase::initialize()/*{{{*/
{
    // Generate the path string.
    _path = _createFilePath();

    // Check the FIFO. Normally, the FIFO should exist with 
    // the right permissions, except sxc has not been run before (in this 
    // directory) or someone tampered with the directory structure.
    try {
        _validateFile();
    } catch (Exception::FileInputException e) {
        // If the FIFO is simply missing, try to create it. In any other case 
        // we have encountered an unexpected error and let it bubble up.
        if (Exception::FileMissing != e.getType())
            throw e;
        _createFile();
    }

    // Everything went fine; path is okay. Open FIFO.
    _fifo.open(_path.c_str());
}

/*}}}*/
void File::InputBase::listen(bool blocking)/*{{{*/
{
    // Prevent application from starting a second thread which would overwrite 
    // the first one in @ref _thread
    if (_isThreadRunning)
        // FIXME
        return;

    // Set flag to indicate that a thread is running.
    _isThreadRunning = true;
    // Start the thread in the background.
    pthread_create(&_thread, NULL, _listen, this);
    // Join the thread when this functions should read in a blocking way.
    if (true == blocking)
        pthread_join(_thread, NULL);
}

/*}}}*/
void File::InputBase::_read()/*{{{*/
{
    // Refuse to read from an invalid FIFO.
    if (!_isFifoValid) {
        throw Exception::FileInputException(Exception::BadFile, "Refusing to read.");
    }

    // Gets filled with everything that is written until the other end closes 
    // the pipe.
    std::string input;
    // Input is read line by line and put in buffer.
    std::string buffer;
    while (getline(_fifo, buffer)) {
        input += buffer;
    }
    _handleInput(input);
}

/*}}}*/
void File::InputBase::close()/*{{{*/
{
    if (_isThreadRunning)
        pthread_cancel(_thread);
        _isThreadRunning = false;
    if (_fifo.is_open())
        _fifo.close();
}

/*}}}*/
void File::InputBase::_createFile()/*{{{*/
{
    // Try to create FIFO with chmod 600.
    if (0 == mkfifo(_path.c_str(), S_IRUSR | S_IWUSR))
        return;

    // Creation of FIFO failed.
    Exception::Type type = Exception::errnoToType(errno);
    std::string message  = "Could not create FIFO " + _path;
    throw Exception::FileInputException(type, message);
}

/*}}}*/
void File::InputBase::_validateFile()/*{{{*/
{
    // Try to get file stats, needed for analyzing the chmod of the file.
    struct stat fstat;
    if (0 != stat(_path.c_str(), &fstat)) {
        Exception::Type type = Exception::errnoToType(errno);
        std::string message  = "Could not get FIFO fstat: " + _path;
        throw Exception::FileInputException(type, message);
    }

    // Is this really a FIFO?
    if (!S_ISFIFO(fstat.st_mode)) {
        std::string message  = "Not a FIFO: " + _path;
        throw Exception::FileInputException(Exception::BadFile, message);
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
        throw Exception::FileInputException(Exception::BadFile, message);
    }

    _isFifoValid = true;
}

/*}}}*/
void *File::InputBase::_listen(void *fifo)/*{{{*/
{
    InputBase *that = (InputBase *) fifo;
    do {
        // _read() reads blocking until the other end closes the pipe. This 
        // loop will always restart _read() after it handled some input and 
        // returned.
        that->_read();
    } while (true);

    return NULL;
}

/*}}}*/

// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker

