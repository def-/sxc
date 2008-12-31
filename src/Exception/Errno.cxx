#line 1 "sxc:Exception/Errno.cxx"
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

