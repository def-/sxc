#line 2 "sxc:Command/Exception/CouldNotSet.cxx"
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

#include <Command/Exception/CouldNotSet.hxx>

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
    CouldNotSet::CouldNotSet(/*{{{*/
      unsigned int index, const char* value) throw()
    : Exception()
    {
      _createMessage(index, value);
      setExitCode(libsxc::Exit::General);
      createBacktrace();
    }

/*}}}*/
    CouldNotSet::CouldNotSet(/*{{{*/
      unsigned int index,
      const char* value,
      const std::exception& cause) throw()
    : Exception(cause)
    {
      _createMessage(index, value);
      setExitCode(libsxc::Exit::General);
      createBacktrace();
    }

/*}}}*/
    CouldNotSet::~CouldNotSet() throw()/*{{{*/
    {
    }

/*}}}*/
      void CouldNotSet::_createMessage(/*{{{*/
        unsigned int index, const char* value) throw()
      {
        char messageBuffer[libsxc::Exception::Exception::MESSAGE_BUFFER_SIZE];
        const char* format = "Could not set value of argument %u to '%s'.";

        // Truncate argument if too long.
        const unsigned int maxLength = MESSAGE_BUFFER_SIZE -20 - strlen(format);
        char arg[maxLength];
        strncpy(arg, value, maxLength - 1);
        arg[maxLength] = '\0';

        sprintf(messageBuffer, format, arg);
        setMessage(messageBuffer);
      }

/*}}}*/
  }
}

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
