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

#ifndef FILE_EXCEPTION_ERRNOTOEXCEPTION_HXX
#define FILE_EXCEPTION_ERRNOTOEXCEPTION_HXX

// INCLUDES/*{{{*/

#include <libsxc/Exception/Exception.hxx>

/*}}}*/


namespace File
{
  namespace Exception
  {
    /** Transforms the passed errno into an exception.
     *
     * For a list of possible errno's and their meaning, look at the following
     * man pages:
     * @li man 2 stat
     * @li man 3 mkfifo
     *
     * @param p_errno The errno that occured and that should be transformed.
     * @param message The message to give to the exception.
     * @return An @ref Exception::Exception that matches the passed errno.
     */
    libsxc::Exception::Exception errnoToException(int p_errno, const char *message);
  }
}

#endif // FILE_EXCEPTION_ERRNOTOEXCEPTION_HXX

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
