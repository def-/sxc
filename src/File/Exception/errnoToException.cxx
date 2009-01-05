#line 2 "sxc:File/Exception/errnoToException.cxx"
// LICENSE/*{{{*/
/*
  sxc - Simple Xmpp Client
  Copyright (C) 2008 Dennis Felsing, Andreas Waidler

  Permission to use, copy, modify, and/or distribute this software for any
  purpose with or without fee is hereby granted, provided that the above
  copyright notice and this permission notice appear in all copies.

  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
/*}}}*/

// INCLUDES/*{{{*/

#include <errno.h>

#include <libsxc/Exception/Exception.hxx>
#include <libsxc/Exit/Code.hxx>
#include <Exit/Code.hxx>

#include <File/Exception/errnoToException.hxx>

#include <File/Exception/AccessDenied.hxx>
#include <File/Exception/BadFile.hxx>
#include <File/Exception/BadPath.hxx>
#include <File/Exception/CloseFailed.hxx>
#include <File/Exception/FileExists.hxx>
#include <File/Exception/FileLocked.hxx>
#include <File/Exception/FileMissing.hxx>
#include <File/Exception/OpenFailed.hxx>
#include <File/Exception/ReadFailed.hxx>
#include <File/Exception/WriteFailed.hxx>

/*}}}*/

namespace File
{
  namespace Exception
  {
    libsxc::Exception::Exception errnoToException(
      int p_errno,
      const char *message)
    {
      switch (p_errno) {
      case EACCES:
        return AccessDenied(message);

      case EEXIST:
        return FileExists(message);

      case ENOENT:
        return FileMissing(message);

      case ELOOP:
      case ENOTDIR:
        return BadPath(message);

      case ENAMETOOLONG:
        return BadFile(message);

      case ENOSPC:
      case EROFS:
        return WriteFailed(message);
      // The following ones should not be needed but may be passed as
      // parameter and could be handled in future versions:
      // case EBADF:
      // case EFAULT:
      // case ENOMEM:
      }

      return libsxc::Exception::Exception(message, libsxc::Exit::General);
    }
  }
}

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
