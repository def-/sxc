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

#ifndef CONTROL_FILE_INPUT_HXX
#define CONTROL_FILE_INPUT_HXX

// INCLUDES/*{{{*/

#include <string>

#include <File/AbcInput.hxx>
#include <Control/Control.hxx>

/*}}}*/

namespace Control
{
    namespace File
    {
        /**
         * @brief Main input class for sxc.
         *
         * Creates the file <JID>/in which handles commands for sxc and
         * communication with the server.
         *
         * @author Andreas Waidler
         */
        class Input : public ::File::AbcInput
        {
            public:
                // Input(Control &control);/*{{{*/

                /**
                 * @brief Initializes the object.
                 *
                 * @param control The Control object.
                 */
                Input(Control &control);

/*}}}*/

            private:
                //Control &_control;/*{{{*/
                /// The control object.
                Control &_control;

/*}}}*/
                // std::string _createPath() const;/*{{{*/

                /**
                 * @brief Returns the path and file name of the FIFO.
                 *
                 * @see File::AbcInput::_createPath()
                 *
                 * @return "$accountName/in"
                 */
                std::string _createPath() const;

/*}}}*/
                // void _handleInput(const std::string &input);/*{{{*/

                /**
                 * @brief Handles input that has been written into the FIFO.
                 *
                 * For a list of valid commands see @ref
                 * Control::Command. The main work will be done by an
                 * instance of that class, this method provides just the
                 * exception handling and creates that object.
                 *
                 * @param input Something that has been written into the FIFO.
                 */
                void _handleInput(const std::string &input);

/*}}}*/
        };
    }
}

#endif // CONTROL_FILE_INPUT_HXX

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
