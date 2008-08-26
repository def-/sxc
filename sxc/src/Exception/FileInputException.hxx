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

#ifndef EXCEPTION_FILEINPUTEXCEPTION_HXX
#define EXCEPTION_FILEINPUTEXCEPTION_HXX

// INCLUDES/*{{{*/

#include <string>
#include <libsxc/Exception/Exception.hxx>
#include <libsxc/Exception/Type.hxx>

/*}}}*/


namespace Exception
{
    /**
     * @brief Exception class for the input file classes.
     * @author Andreas Waidler
     */
    class FileInputException : public libsxc::Exception::Exception
    {
        public:
            //FileInputException(Type type, string &message)/*{{{*/

            /**
             * @brief Default constructor, does only call parent constructor.
             *
             * @param type The type of the exception.
             * @param message The message to describe what exactly happened as
             *        a reference.
             */
            FileInputException(
                libsxc::Exception::Type type,
                std::string &message);

/*}}}*/
            //FileInputException(Type type, string *message)/*{{{*/

            /**
             * @brief Overloaded default constructor, calls parent constructor.
             *
             * @param type The type of the exception.
             * @param message The message to describe what exactly happened as
             *        a pointer.
             */
            FileInputException(
                libsxc::Exception::Type type,
                const char *message);

/*}}}*/

        protected:
            /// @see Exception::createDescription()
            virtual void createDescription() throw();

        private:

    };
}

#endif // EXCEPTION_FILEINPUTEXCEPTION_HXX


// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker

