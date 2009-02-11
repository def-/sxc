#line 2 "sxc:Command/Exception/CouldNotAdd.cxx"
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

#include <Command/Exception/CouldNotAdd.hxx>

#include <Command/Exception/Exception.hxx>
#include <libsxc/Exit/Code.hxx>

#include <exception>
#include <cstring>
#include <cstdio>

/*}}}*/

namespace Command
{
  namespace Exception
  {
    CouldNotAdd::CouldNotAdd(const char* argument) throw()/*{{{*/
    : Exception()
    {
      _createMessage(argument);
      setExitCode(libsxc::Exit::General);
      createBacktrace();
    }

/*}}}*/
    CouldNotAdd::CouldNotAdd(/*{{{*/
      const char* argument, const std::exception& cause) throw()
    : Exception(cause)
    {
      _createMessage(argument);
      setExitCode(libsxc::Exit::General);
      createBacktrace();
    }

/*}}}*/
    CouldNotAdd::~CouldNotAdd() throw()/*{{{*/
    {
    }

/*}}}*/
      void CouldNotAdd::_createMessage(const char* argument) throw()/*{{{*/
      {
        char messageBuffer[libsxc::Exception::Exception::MESSAGE_BUFFER_SIZE];
        const char* format = "Could not add argument '%s'.";

        // Truncate argument if too long.
        const unsigned int maxLength = MESSAGE_BUFFER_SIZE - 1 - strlen(format);
        char arg[maxLength];
        strncpy(arg, argument, maxLength - 1);
        arg[maxLength] = '\0';

        sprintf(messageBuffer, format, arg);
        setMessage(messageBuffer);
      }

/*}}}*/
  }
}

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
