// LICENSE/*{{{*/
/*
  sxc - Simple Xmpp Client
  Copyright (C) 2008 Dennis Felsing, Andreas Waidler

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/*}}}*/

/* $Id$ */


#ifndef EXCEPTION_EXCEPTION_H
#define EXCEPTION_EXCEPTION_H


// INCLUDE/*{{{*/

#include <string>
#include <exception>

#include "Type.h"

/*}}}*/

namespace Exception
{
    /**
     * @class Exception
     * @author Dennis Felsing
     * @brief An exception base class.
     */
    class Exception : public std::exception
    {
        public:
            //virtual ~Exception() throw() {}/*{{{*/

            /**
             * @brief The destructor.
             *
             * Has to be set so the compiler doesn't bug about the destructor
             * having a looser throw specifier.
             */
            virtual ~Exception() throw();

/*}}}*/
            //virtual const char *what() const throw();/*{{{*/

            /**
             * @brief Get a C-style character string of @ref getMessage().
             *
             * Has to be implemented as a backward compatibility to exception.
             *
             * @return A C-style character string describing the exception.
             */
            virtual const char *what() const throw();

/*}}}*/

            //void setMessage(Type type, std::string message) throw();/*{{{*/

            /**
             * @brief Set the given values.
             *
             * This function just calls @ref doSetMessage().
             *
             * @param type The type of the exception.
             * @param message A text describing the exception more verbose.
             */
            void setMessage(Type type, std::string message) throw();

/*}}}*/
            //virtual void doSetMessage(Type type, std::string message) = 0;/*{{{*/

            /**
             * @brief Set the given values.
             *
             * This function does the real work and has to be implemented by
             * child classes that can be thrown.
             *
             * @param type The type of the exception.
             * @param message A text describing the exception more verbose.
             */
            virtual void doSetMessage(Type type, std::string message) = 0;

/*}}}*/
            //const std::string &getMessage() const throw();/*{{{*/

            /**
             * @brief Get a const reference to the message of the exception.
             *
             * @return A text describing the exception more verbose.
             */
            const std::string &getMessage() const throw();

/*}}}*/
            //Type getType() const throw();/*{{{*/

            /**
             * @brief Get the type of the exception.
             * @return The type of the exception.
             */
            Type getType() const throw();

/*}}}*/

        private:
            //Exception(Type type, std::string message) throw();/*{{{*/

            /**
             * @brief The constructor.
             *
             * @param type The type of the exception.
             * @param message A text describing the exception more verbose.
             */
            Exception(Type type, std::string message) throw();

/*}}}*/

            //Type _type;/*{{{*/

            /// The type of the exception.
            Type _type;

/*}}}*/
            //std::string _message;/*{{{*/

            /// A text describing the exception more verbose.
            std::string _message;

/*}}}*/
    };
}


#endif // EXCEPTION_EXCEPTION_H
// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
