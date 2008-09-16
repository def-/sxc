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

#ifndef CONTACT_FILE_INPUT_HXX
#define CONTACT_FILE_INPUT_HXX

// INCLUDES/*{{{*/

#include <string>

#include <File/AbcInput.hxx>
#include <Contact/Contact.hxx>
#include <Control/Control.hxx>

/*}}}*/

namespace Contact
{
    namespace File
    {
        /**
         * @brief Input file for communication with contacts.
         *
         * Creates the file <JID>/<Contact>/in which handles communication with 
         * a contact and the corresponding commands.
         *
         * @author Andreas Waidler
         */
        class Input : public ::File::AbcInput
        {
            public:
                // Input(Control &control, Contact &contact);/*{{{*/

                /**
                 * @brief Default constructor.
                 *
                 * @note Call @ref initialize() before using the object.
                 *
                 * @param contact Contact object. Stored as a reference 
                 *                internally.
                 */
                Input(Control::Control &control, Contact &contact);

/*}}}*/

            protected:

            private:
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
                //Control &_control;/*{{{*/
                /// The control object.
                Control::Control &_control;

/*}}}*/
                //Contact &_contact;/*{{{*/
                /// The contact object.
                Contact &_contact;

/*}}}*/

                // void _handleInput(const std::string &input);/*{{{*/

                /**
                 * @brief Handles input that has been written into the FIFO.
                 *
                 * For a list of valid commands see @ref
                 * Contact::Command::Command. The main work will be done by an
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

#endif // CONTACT_FILE_INPUT_HXX

// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
