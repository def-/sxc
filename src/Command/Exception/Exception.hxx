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

#ifndef COMMAND_EXCEPTION_EXCEPTION_HXX
#define COMMAND_EXCEPTION_EXCEPTION_HXX

// INCLUDE/*{{{*/

#include <libsxc/Exception/Exception.hxx>

#include <exception>

/*}}}*/

namespace Command
{
  namespace Exception
  {
    /**
     * @brief Base class for exceptions thrown by the command framework.
     */
    class Exception : virtual public libsxc::Exception::Exception
    {
      public:
        // Exception(const char* message) throw();/*{{{*/

        /**
         * @brief Default constructor.
         *
         * @param message C-string describing the error.
         */
        Exception(const char* message) throw();

/*}}}*/
        // Exception(const char* message, const std::exception& cause) throw();/*{{{*/

        /**
         * @brief Extended default constructor using a backtrace.
         *
         * @param message C-string describing the error.
         * @param cause The cause for the throwing of this exception.
         */
        Exception(const char* message, const std::exception& cause) throw();

/*}}}*/
        // virtual ~Exception() throw()/*{{{*/

        /**
         * @brief Virtual destructor.
         */
        virtual ~Exception() throw();

/*}}}*/

      protected:
        // Exception() throw();/*{{{*/

        /**
         * @see libsxc::Exception::Exception::Exception()
         */
        Exception() throw();

/*}}}*/
        // Exception(const std::exception& cause) throw();/*{{{*/

        /**
         * @see libsxc::Exception::Exception::Exception(const std::exception&)
         */
        Exception(const std::exception& cause) throw();

/*}}}*/
    };
  }
}

#endif // COMMAND_EXCEPTION_EXCEPTION_HXX
// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
