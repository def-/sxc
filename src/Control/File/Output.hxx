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

#ifndef CONTROL_FILE_OUTPUT_HXX
#define CONTROL_FILE_OUTPUT_HXX

// INCLUDES/*{{{*/

#include <string>
#include <File/AbcOutput.hxx>

/*}}}*/

namespace Control
{
    namespace File
    {
        /**
         * @brief Main output class for sxc.
         *
         * Creates the file $JID/out which displays messages from sxc and from
         * the server.
         *
         * @author Andreas Waidler
         */
        class Output : public ::File::AbcOutput
        {
            public:
                // Output(Control::Control &control);/*{{{*/

                /**
                 * @brief Initializes the object.
                 *
                 * @param control Central object, holding account information
                 */
                Output(Control::Control &control);

/*}}}*/

            protected:


            private:
                // Control::Control *_control;/*{{{*/

                /// Central control object, used for error handling or getting
                /// account information.
                Control::Control *_control;

/*}}}*/
                // std::string _createPath() const;/*{{{*/

                /**
                 * @brief Creates a string containing the path of this file.
                 *
                 * @see File::AbcOutput::_createPath()
                 *
                 * @return $accountName/out
                 */
                std::string _createPath() const;

/*}}}*/
                // std::string _format(const std::string &output) const;/*{{{*/

                /**
                 * @brief Formats the output.
                 *
                 * @param output String to be formatted.
                 * @return A formatted string.
                 */
                std::string _format(const std::string &output) const;

/*}}}*/
        };
    }
}

#endif // CONTROL_FILE_OUTPUT_HXX

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
