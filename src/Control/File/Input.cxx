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
#include <Control/File/Input.hxx>
#include <Control/Command/Command.hxx>
#include <Exception/InputException.hxx>
#include <libsxc/Exception/Exception.hxx>

/*}}}*/

namespace Control
{
    namespace File
    {
        Input::Input(const std::string &accountName)/*{{{*/
        : _accountName(accountName)
        {
            initialize();
        }

        /*}}}*/
        const std::string &Input::_createPath()/*{{{*/
        {
            return _accountName + "/in";
        }

        /*}}}*/
        void Input::_handleInput(const std::string &input)/*{{{*/
        {
            Control control = Control::get();
            try {
                Command::Command command(input);
                command.execute();
            } catch (Exception::InputException &e) {
                // Just an invalid input, nothing serious.
                control.handleError(e);
            } catch (libsxc::Exception::Exception &e) {
                // This may be something more serious.
                // TODO: Fix handleError() to make use of stderr
                control.handleError(e);
            } catch (std::exception &e) {
                // This is *really* unexpected.
                printErr(e.what());
                control.print(e.what());
            }
        }

        /*}}}*/
    }
}

// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
