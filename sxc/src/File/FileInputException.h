// TODO
// - remove _thrower and anything concerning an InputBase object. This is not 
//   needed, i think!
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

#ifndef FILE_FILEINPUTEXCEPTION_H
#define FILE_FILEINPUTEXCEPTION_H

// INCLUDES/*{{{*/

#include <exception>
#include <string>
#include "File.h"
#include "InputBase.h"

/*}}}*/


namespace File
{
    /**
     * @class File::FileInputException
     * @brief Exception class for the input file classes.
     *
     * @author Andreas Waidler
     */
    class FileInputException : public exception
    {
        public:
            // FileInputException(InputBase &, ErrorType, string);/*{{{*/

            /**
             * @brief Constructor, sets passed parameters.
             *
             * @param thrower Reference of the object that threw this exception.
             * @param type The ErrorType that occurred.
             * @param message The message that should be used to notify the 
             *        user.
             */
            FileInputException(
                File::InputBase &thrower,
                Control::Error::ErrorType type,
                std::string message);

/*}}}*/
            // virtual const char *what() const throw();/*{{{*/

            /**
             * @brief Returns the error message.
             *
             * The C-String returned is @a message from @ref 
             * FileOutputException().
             *
             * @see getMessage() which does the same but returns a std::string
             *
             * @return A message to notify the user with.
             */
            virtual const char *what() const throw();

/*}}}*/
            // File::InputBase &getThrower();/*{{{*/

            /** Returns reference to the object that threw this exception.
             *
             * @return Refernce of @ref _thrower.
             */
            File::InputBase &getThrower();

/*}}}*/
            // Control::Error::ErrorType getErrorType() const throw();/*{{{*/

            /** Returns ErrorType of this exception.
             * 
             * @return An element of the Control::Error::ErrorType enum.
             */
            const Control::Error::ErrorType getErrorType() const throw();

/*}}}*/
            // std::string getMessage();/*{{{*/

            /** Returns the error message.
             *
             * @return Error message of this exception.
             */
            std::string getMessage();

/*}}}*/

        private:
            /// Pointer to the object that threw this exception.
            File::InputBase *_thrower;
            /// Error type of this exception.
            Control::Error::ErrorType _type;
            // Message of this exception.
            std::string _message;





    };
}

#endif // FILE_FILEINPUTEXCEPTION_H

// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker

