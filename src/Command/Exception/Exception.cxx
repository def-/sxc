#line 2 "sxc:Command/Exception/Exception.cxx"
// LICENSE/*{{{*/
/*
  libsxc
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

// INCLUDE/*{{{*/

#include <Command/Exception/Exception.hxx>

#include <libsxc/Exception/Exception.hxx>
#include <libsxc/Exit/Code.hxx>

#include <exception>

/*}}}*/

namespace Command
{
  namespace Exception
  {
    Exception::Exception(const char* message) throw()/*{{{*/
    : libsxc::Exception::Exception(message, libsxc::Exit::General)
    {
    }

/*}}}*/
    Exception::Exception(/*{{{*/
      const char* message, const std::exception& cause) throw()
    : libsxc::Exception::Exception(message, libsxc::Exit::General, cause)
    {
    }

/*}}}*/
    Exception::~Exception() throw()/*{{{*/
    {
    }

/*}}}*/

    Exception::Exception() throw()/*{{{*/
    : libsxc::Exception::Exception()
    {
    }

/*}}}*/
    Exception::Exception(const std::exception& cause) throw()/*{{{*/
    : libsxc::Exception::Exception(cause)
    {
    }

/*}}}*/
  }
}

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
