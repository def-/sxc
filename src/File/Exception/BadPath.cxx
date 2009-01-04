#line 2 "sxc:File/Exception/BadPath.cxx"
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

#include <File/Exception/BadPath.hxx>

#include <libsxc/Exception/Exception.hxx>
#include <libsxc/Exception/Type.hxx>

#include <exception>
#include <cstring>
#include <cstdio>

/*}}}*/

namespace File
{
  namespace Exception
  {
    BadPath::BadPath(const char* name) throw()/*{{{*/
    : libsxc::Exception::Exception()
    {
      _createMessage(name);
      setType(libsxc::Exception::BadPath);
      createBacktrace();
    }

/*}}}*/
    BadPath::BadPath(/*{{{*/
      const char* name,
      const std::exception& cause) throw()
    : libsxc::Exception::Exception(cause)
    {
      _createMessage(name);
      setType(libsxc::Exception::BadPath);
      createBacktrace();
    }

/*}}}*/
    void BadPath::_createMessage(const char* name) throw()/*{{{*/
    {
      char messageBuffer[libsxc::Exception::Exception::MESSAGE_BUFFER_SIZE];
      const char* format = "Bad path: '%s'";
      // Allowed length of name is buffer size - null char - format length.
      const unsigned int maxLength = MESSAGE_BUFFER_SIZE - 1 - strlen(format);
      char truncatedName[maxLength + 1];
      strncpy(truncatedName, name, maxLength - 1);
      truncatedName[maxLength] = '\0';
      sprintf(messageBuffer, format, name);
      setMessage(messageBuffer);
    }

/*}}}*/
  }
}

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
