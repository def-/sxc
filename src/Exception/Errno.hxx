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


/**
 * @file Errno.hxx
 * @brief Contains functions for handling the system errno variable.
 */

#ifndef EXCEPTION_ERRNO_HXX
#define EXCEPTION_ERRNO_HXX

// INCLUDES/*{{{*/

#include <libsxc/Exception/Type.hxx>

/*}}}*/


namespace Exception
{

    /** Transforms the passed errno into an exception type.
     *
     * For a list of possible errno's and their meaning, look at the following
     * man pages:
     * @li man 2 stat
     * @li man 3 mkfifo
     *
     * @param p_errno The errno that occured and that should be transformed.
     * @return An Exception::Type that matches the passed errno.
     */
    libsxc::Exception::Type errnoToType(int p_errno);
}

#endif // EXCEPTION_ERRNO_HXX

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker

