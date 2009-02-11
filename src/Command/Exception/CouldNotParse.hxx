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

#ifndef COMMAND_EXCEPTION_COULDNOTPARSE_HXX
#define COMMAND_EXCEPTION_COULDNOTPARSE_HXX

// INCLUDE/*{{{*/

#include <Command/Exception/Exception.hxx>

#include <exception>

/*}}}*/

namespace Command
{
  namespace Exception
  {
    /**
     * @brief To be thrown when an input could not been parsed.
     *
     * Thrown by Parser::parse().
     */
    class CouldNotParse : public Exception
    {
      public:
        // CouldNotParse(const char* input) throw();/*{{{*/

        /**
         * @brief Default constructor.
         *
         * @param input The input that had to be parsed.
         */
        CouldNotParse(const char* input) throw();

/*}}}*/
        // CouldNotParse(const char*, const std::exception&) throw();/*{{{*/

        /**
         * @brief Extended default constructor using a backtrace.
         *
         * @param input The input that had to be parsed.
         * @param cause The cause for the throwing of this exception.
         */
        CouldNotParse(const char* input, const std::exception& cause) throw();

/*}}}*/
        // virtual ~CouldNotParse() throw()/*{{{*/

        /**
         * @brief Virtual destructor.
         */
        virtual ~CouldNotParse() throw();

/*}}}*/
      private:
        // void _createMessage(const char*) throw();/*{{{*/

        /**
         * @brief Creates the message describing this exception.
         * @param input The input that had to be parsed.
         */
        void _createMessage(const char* input) throw();

/*}}}*/
    };
  }
}

#endif // COMMAND_EXCEPTION_COULDNOTPARSE_HXX
// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
