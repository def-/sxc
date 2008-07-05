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
#include <ifstream>
#include <pthread.h>
#include <sys/stat.h>
#include <errno.h>
#include "File.h"
#include "InputBase.h"

/*}}}*/


File::InputBase::InputBase()/*{{{*/
: _threadIsRunning(FALSE)
{ }

/*}}}*/
File::InputBase::~InputBase()/*{{{*/
{
    close();
}

/*}}}*/
void File::InputBase::initialize()/*{{{*/
{
    // Generate the path string.
    _path = _createPath();

    // Check the permissions of the FIFO. Normally, the FIFO should exist with 
    // the right permissions, except sxc has not been run before (in this 
    // directory) or someone tampered with the directory structure.
    try {
        _checkPermissions();
    } catch (File::FileInputException e) {
        // If the FIFO is simply missing, try to create it. In any other case 
        // we have encountered an unexpected error and let it bubble up.
        if (e.getErrorType() != Control::Error::Type::ErrorFileMissing)
            throw e;
        _tryCreate();
    }

    // Everything went fine; path is okay. Open FIFO.
    _fifo.open(_path);
}

/*}}}*/
void File::InputBase::listen(bool blocking = FALSE)/*{{{*/
{
    _threadIsRunning = TRUE;
    pthread_create(&_thread, NULL, _pthreadListen, NULL);
    if (TRUE == blocking)
        pthread_join(_thread, NULL);
}

/*}}}*/
void File::InputBase::read()/*{{{*/
{
    std::string input, buffer;
    while (getline(_fifo, buffer)) {
        input += buffer;
    }
    _handle(input);
}

/*}}}*/
void File::InputBase::close()/*{{{*/
{
    if (TRUE == _threadIsRunning)
        pthread_cancel(_thread);
        _threadIsRunning = FALSE;
    if (_fifo.is_open())
        _fifo.close();
}

/*}}}*/
void File::InputBase::_throwErrno(/*{{{*/
    int errno,
    Control::Error::Severity severity,
    std::string origin)
{
    std::string message = "Error while setting up FIFO " + _path + ": ";
    message += origin + ": ";

    switch (errno) {
    case EEXIST:
        throw FileInputException(
            Control::Error::Type::ErrorFileExists,
            severity,
            message + "File exists.");

    case ENOENT:
    case ENOTDIR:
        throw FileInputException(
            Control::Error::Type::ErrorInvalidPath,
            severity,
            message + "Invalid path.");

    case ELOOP:
    case ENAMETOOLONG:
        throw FileInputException(
            Control::Error::Type::ErrorInvalidPath,
            severity,
            message + "Bad name.");

    case EROFS:
    case EACCES:
        throw FileInputException(
            Control::Error::Type::ErrorFileCreationPermission,
            severity,
            message + "Permission denied.");

    case ENOMEM:
        // TODO
    case ENOSPC:
        throw FileInputException(
            Control::Error::Type::ErrorFileOutOfSpace,
            severity,
            message + "No space left.");

    default:
        throw FileInputException(
            Control::Error::Type::ErrorFilePermission,
            severity,
            message + "Unknown error, errno=" + errno);
    }
}

/*}}}*/
void File::InputBase::_tryCreate()/*{{{*/
{
    // Try to create FIFO with chmod 600.
    if (0 == mkfifo(_path.c_str(), S_IRUSR | S_IWUSR))
        return;

    // Creation failed, create an exception and throw it.
    _throwErrno(errno,Control::Error::Severity::SeverityCritical,"_tryCreate()")
}

/*}}}*/
void File::InputBase::_checkPermissions()/*{{{*/
{
    struct stat fileStats;
    // Try to get file stats, needed for analyzing the chmod of the file.
    if (0 != stat(_path.c_str(), &fileStats)) {
       ELOOP  Too many symbolic links encountered while traversing the path.

       ENOMEM Out of memory (i.e., kernel memory).

        }
    }

    std::cout << std::boolalpha
              << S_ISFIFO(stats.st_mode) << std::endl
              << (stats.st_mode & S_IRUSR) << std::endl
              << (stats.st_mode & S_IWUSR) << std::endl
              << (stats.st_mode & S_IRGRP) << std::endl
              << (stats.st_mode & S_IWGRP) << std::endl
              << (stats.st_mode & S_IROTH) << std::endl
              << (stats.st_mode & S_IWOTH) << std::endl
              ;




}/*}}}*/
void *File::InputBase::_pthreadListen(void *ptr)/*{{{*/
{
    // TODO
}/*}}}*/
// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
