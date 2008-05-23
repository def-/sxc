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

// #include <string>
// #include <istream>
// #include <pthread.h>
#include "File.h"
#include "InputBase.h"

/*}}}*/


File::InputBase::InputBase()
: _threadIsRunning(false)
{
}

File::InputBase::~InputBase()
{
    if (true == _threadIsRunning)



void File::InputBase::initialize()
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
        if (e.getErrorType() != Control::Error::ErrorType::ErrorFileMissing)
            throw e;
        _tryCreate();
    }

    // Everything went fine; path is okay. Initialize _fifo with it.
    _fifo(_path);



// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
