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

#include <libsxc/Exception/Type.hxx>

#include <Exception/Errno.hxx>

/*}}}*/

namespace Exception
{
    libsxc::Exception::Type errnoToType(int p_errno)
    {
        libsxc::Exception::Type result = libsxc::Exception::General;

        switch (p_errno) {
        case EACCES:
            result = libsxc::Exception::AccessDenied;
            break;

        case EEXIST:
            result = libsxc::Exception::FileExists;
            break;

        case ENOENT:
            result = libsxc::Exception::FileMissing;
            break;

        case ELOOP:
        case ENOTDIR:
            result = libsxc::Exception::BadPath;
            break;

        case ENAMETOOLONG:
            result = libsxc::Exception::BadFile;
            break;

        case ENOSPC:
        case EROFS:
            result = libsxc::Exception::WriteFailed;
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


// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker

