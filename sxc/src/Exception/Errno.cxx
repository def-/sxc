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

#include <errno.h>

#include <Exception/Errno.hxx>
#include <Exception/Type.hxx>

/*}}}*/

namespace Exception
{
    Type errnoToType(int p_errno)
    {
        Type result = General;

        switch (p_errno) {
        case EACCES:
            result = AccessDenied;
            break;

        case EEXIST:
            result = FileExists;
            break;

        case ENOENT:
            result = FileMissing;
            break;

        case ELOOP:
        case ENOTDIR:
            result = BadPath;
            break;

        case ENAMETOOLONG:
            result = BadFile;
            break;

        case ENOSPC:
        case EROFS:
            result = WriteFailed;
            break;
        // The following ones should not be needed but may be passed as
        // parameter and could be handled in future versions:
        // case EBADF:
        // case EFAULT:
        // case ENOMEM:
        }

        return result;
    }
}


// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker

