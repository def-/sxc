// LICENSE/*{{{*/
/*
  Copyright (C) 2008 Andreas Waidler, Dennis Felsing

  This program is free software: you can redistribute it and/or modify it 
  under the terms of the GNU General Public License as published by the Free 
  Software Foundation, either version 3 of the License, or (at your option) 
  any later version.

  This program is distributed in the hope that it will be useful, but WITHOUT 
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
  FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for 
  more details.

  You should have received a copy of the GNU General Public License along with 
  this program. If not, see <http://www.gnu.org/licenses/>.
 */
/*}}}*/


#ifndef CONTROL_ERROR_H
#define CONTROL_ERROR_H


// INCLUDE/*{{{*/

#include <gloox/gloox.h>

#include <string>

/*}}}*/


namespace Control
{
    /**
     * @class Error
     * @author Dennis Felsing
     * @brief A class representing an error.
     *
     * Creating an object of this class outputs it.
     */
    class Error
    {
        public:
            //enum ErrorType/*{{{*/

            /// Error types and exit codes at the same time.
            enum ErrorType
            {
                ErrorNoError = 0, //< No error occured.
                ErrorGeneral = 1,
                // Parameter errors.
                ErrorParametersInvalid = 10,
                ErrorPortInvalid,
                ErrorJidInvalid,
                // File errors.
                ErrorFilePermission = 20,
                ErrorFileCreationPermission,
                ErrorFileOutOfSpace
            };
/*}}}*/

            //Error(/*{{{*/

            /** The constructor
             *
             * @param errorType The Type of the error.
             * @param message Additional information for some errors.
             * @param isCritical If true print to stderr and exit, else print
             *        to the Control output file.
             */
            Error(
                ErrorType errorType,
                std::string message = gloox::EmptyString,
                bool isCritical = false);

/*}}}*/

        private:
            //static const std::string outputPrefix;/*{{{*/

            /// The text printed before every error output to the console.
            static const std::string outputPrefix;

/*}}}*/

            //const std::string format(/*{{{*/

            /** Generate a formatted error text.
             *
             * @param errorType The type of the error.
             * @param message Additional information some exit codes can
             *        have.
             * @return The generated error text.
             */
            const std::string format(
                ErrorType errorType,
                const std::string message = gloox::EmptyString);

/*}}}*/
    };
}

#endif // CONTROL_ERROR_H
