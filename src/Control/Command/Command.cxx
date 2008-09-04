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
#   include <print.hxx>
#endif

#include <string>
#include <deque>
#include <map>

#include <Control/Command/Command.hxx>
#include <Exception/InputException.hxx>
#include <libsxc/Exception/Exception.hxx>
#include <Control/Control.hxx>
#include <Control/Roster.hxx>

/*}}}*/

using CommandParser::commandMap;
using CommandParser::command;
using CommandParser::param;

namespace Control
{
    namespace Command
    {
        Command::Command(Control &control, const std::string &command)/*{{{*/
        : AbcCommandParser(command),
          _control(control)
        {
        }

    /*}}}*/
        Command::~Command()/*{{{*/
        {
        }

    /*}}}*/
        CommandParser::commandMap Command::_createCommands() const/*{{{*/
        {
            commandMap map;
            commandMap::iterator it = map.begin();

            it = map.insert(it, command("ack", param(1, false)));
            it = map.insert(it, command("add", param(1, true )));
            it = map.insert(it, command("del", param(1, false)));
            it = map.insert(it, command("msg", param(2, false)));
            it = map.insert(it, command("pgp", param(2, false)));
            it = map.insert(it, command("pwd", param(1, false)));
            it = map.insert(it, command("set", param(1, true )));
            it = map.insert(it, command("sub", param(1, true )));
            it = map.insert(it, command("usc", param(1, false)));

            return map;
        }

/*}}}*/
        void Command::execute()/*{{{*/
        {
            parse();
            const std::deque<std::string> parsed = getParsed();
            const std::string name = parsed.at(0);

            Roster &roster = _control.getRoster();

            if ("ack" == name) {
                roster.acknowledgeSubscription(parsed.at(1));
            } else if ("add" == name) {
                // TODO Can be optimized.
                roster.addContact(parsed.at(1));
            } else if ("del" == name) {
                roster.removeContact(parsed.at(1));
            } else if ("msg" == name) {
                _control.sendMessage(parsed.at(1), parsed.at(2));
            } else if ("pgp" == name) {
                const std::string action = parsed.at(1);
                // FIXME add pgp
                if ("chk" == action) {
                } else if ("dec" == action) {
                } else if ("enc" == action) {
                } else if ("sig" == action) {
                } else {
                    libsxc::Exception::Type type =
                        libsxc::Exception::InvalidCommand;
                    std::string message = "Unknown parameter '"
                                        + action + "' for command 'pgp'.";
                    throw Exception::InputException(type, message);
                }
                // FIXME add pgp
                throw Exception::InputException(
                    libsxc::Exception::General, "Unimplemented.");
            } else if ("pwd" == name) {
                _control.setPassphrase(parsed.at(1));
            } else if ("set" == name) {
                // FIXME
                //if (3 == parsed.size())
                //    _control.setPresence(parsed.at(1), parsed.at(2));
                //else
                //    _control.setPresence(parsed.at(1), parsed.at(2), parsed.at(3));
            } else if ("sub" == name) {
                roster.subscribe(parsed.at(1), parsed.at(2));
            } else if ("usc" == name) {
                roster.unsubscribe(parsed.at(1), parsed.at(2));
            } else {
                libsxc::Exception::Type t = libsxc::Exception::InvalidCommand;
                std::string message = "Unknown name: " + name;
                throw Exception::InputException(t, message);
            }
        }

/*}}}*/
    }
}

// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
