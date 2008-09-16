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

// INCLUDES/*{{{*/

#ifdef HAVE_CONFIG_H
#   include <config.hxx>
#endif

#include <deque>
#include <string>
#include <exception>

#include <print.hxx>
#include <Control/Control.hxx>
#include <Contact/Contact.hxx>
#include <Contact/File/Input.hxx>
#include <Contact/Command.hxx>
#include <Exception/InputException.hxx>
#include <libsxc/Exception/Exception.hxx>

/*}}}*/

namespace Contact
{
    namespace File
    {
        Input::Input(Control::Control &control, Contact &contact)/*{{{*/
        : _control(control),
          _contact(contact)
        {
        }

/*}}}*/
        std::string Input::_createPath() const/*{{{*/
        {
            return _control.getJid().bare() + _contact.getJid().bare() + "/in";
        }

/*}}}*/
        void Input::_handleInput(const std::string &input)/*{{{*/
        {
            /* // TODO
            try {
                Command::Command command(_contact, input);
                command.execute();
            } catch (Exception::InputException &e) {
                // Just an invalid input, nothing serious.
                _contact.handleError(e);
            } catch (libsxc::Exception::Exception &e) {
                // This may be something more serious.
                // TODO: Fix handleError() to make use of stderr
                _contact.handleError(e);
            } catch (std::exception &e) {
                // This is *really* unexpected.
                printErr(e.what());
                _contact.print(e.what());
            }
            */
        }

/*}}}*/
    }
}

// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
