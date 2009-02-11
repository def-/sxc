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

#ifndef COMMAND_EXCEPTION_COULDNOTSET_HXX
#define COMMAND_EXCEPTION_COULDNOTSET_HXX

// INCLUDE/*{{{*/

#include <Command/Exception/Exception.hxx>

#include <exception>

/*}}}*/

namespace Command
{
  namespace Exception
  {
    /**
     * @brief To be thrown when an argument could not be set.
     *
     * Thrown by Command::set().
     */
    class CouldNotSet : virtual public Exception
    {
      public:
        // CouldNotSet(unsigned int index, const char* argument) throw();/*{{{*/

        /**
         * @brief Default constructor.
         *
         * @param index Index of the argument that could not be set.
         * @param value The value of the argument that could not be set.
         */
        CouldNotSet(unsigned int index, const char* value) throw();

/*}}}*/
        // CouldNotSet(uint, const char*, const std::exception&) throw();/*{{{*/

        /**
         * @brief Extended default constructor using a backtrace.
         *
         * @param index Index of the argument that could not be set.
         * @param value The value of the argument that could not be set.
         * @param cause The cause for the throwing of this exception.
         */
        CouldNotSet(
          unsigned int index,
          const char* value,
          const std::exception& cause
        ) throw();

/*}}}*/
        // virtual ~CouldNotSet() throw()/*{{{*/

        /**
         * @brief Virtual destructor.
         */
        virtual ~CouldNotSet() throw();

/*}}}*/
      private:
        // void _createMessage(const char* argument) throw();/*{{{*/

        /**
         * @brief Creates the message describing this exception.
         * 
         * @param index Index of the argument that could not be set.
         * @param value The value of the argument which could not be set.
         */
        void _createMessage(unsigned int index, const char* value) throw();

/*}}}*/
    };
  }
}

#endif // COMMAND_EXCEPTION_COULDNOTSET_HXX
// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
