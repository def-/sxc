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

#include <print.hxx>

#include <stdexcept>
#include <string>
#include <sstream>
#include <deque>
#include <map>

#include <Control/Command.hxx>
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
        it = map.insert(it, command("dec", param(1, false)));
        it = map.insert(it, command("add", param(1, false)));
        it = map.insert(it, command("del", param(1, false)));
        it = map.insert(it, command("msg", param(2, false)));
        it = map.insert(it, command("pgp", param(2, false)));
        it = map.insert(it, command("pwd", param(1, false)));
        it = map.insert(it, command("set", param(1, true)));
        it = map.insert(it, command("pri", param(1, false)));
        it = map.insert(it, command("sub", param(1, true)));
        it = map.insert(it, command("usc", param(1, true)));

        return map;
    }

/*}}}*/
    void Command::execute()/*{{{*/
    {
        // FIXME Catch exceptions.
        try {
            parse();
            const std::deque<std::string> parsed = getParsed();
            const std::string name = parsed.at(0);

            Roster &roster = _control.getRoster();

            if ("ack" == name) {/*{{{*/
                roster.acknowledgeSubscription(parsed.at(1));
/*}}}*/
            } else if ("dec" == name) {/*{{{*/
                roster.declineSubscription(parsed.at(1));
/*}}}*/
            } else if ("add" == name) {/*{{{*/
                roster.addContact(parsed.at(1));
/*}}}*/
            } else if ("del" == name) {/*{{{*/
                roster.removeContact(parsed.at(1));
/*}}}*/
            } else if ("msg" == name) {/*{{{*/
                _control.sendMessage(parsed.at(1), parsed.at(2));
/*}}}*/
            } else if ("pgp" == name) {/*{{{*/
                const std::string action = parsed.at(1);
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
/*}}}*/
            } else if ("pwd" == name) {/*{{{*/
                _control.setPassphrase(parsed.at(1));
/*}}}*/
            } else if ("set" == name) {/*{{{*/
                gloox::Presence::PresenceType presence;
                const std::string presenceStr = parsed.at(1);
                if ("available" == presenceStr) {
                    presence = gloox::Presence::Available;
                } else if ("chat" == presenceStr) {
                    presence = gloox::Presence::Chat;
                } else if ("away" == presenceStr) {
                    presence = gloox::Presence::Away;
                } else if ("busy" == presenceStr) {
                    presence = gloox::Presence::DND;
                } else if ("xaway" == presenceStr) {
                    presence = gloox::Presence::XA;
                } else if ("invisible" == presenceStr) {
                    presence = gloox::Presence::Unavailable;
                } else if ("offline" == presenceStr) {
                    _control.disconnect();
                    return;
                } else {
                    // FIXME: Exceptions: Accept message as reference, too
                    std::string message = "Not a state to :set : '"
                                        + presenceStr + "'";
                    throw Exception::InputException(
                        libsxc::Exception::InvalidCommand, message);
                }

                if (2 == parsed.size())
                    _control.setPresence(presence);
                else
                    _control.setPresence(presence, parsed.at(2));
/*}}}*/
            } else if ("pri" == name) {/*{{{*/
                int priority;

                std::istringstream ss;
                ss.str(parsed.at(1));
                ss >> priority;

                if (priority > 127 || priority < -128) {
                    libsxc::Exception::Type type =
                        libsxc::Exception::InvalidCommand;
                    std::string message =
                        "Invalid parameter \"" + parsed.at(1) +
                        "\" for command \"pri\". Has to be a number between " +
                        "-128 and 127";
                    throw Exception::InputException(type, message);
                }

                _control.setPriority(priority);
/*}}}*/
            } else if ("sub" == name) {/*{{{*/
                roster.subscribe(parsed.at(1), parsed.at(2));
/*}}}*/
            } else if ("usc" == name) {/*{{{*/
                roster.unsubscribe(parsed.at(1), parsed.at(2));
/*}}}*/
            } else {/*{{{*/
                libsxc::Exception::Type t = libsxc::Exception::InvalidCommand;
                std::string message = "Unknown name: " + name;
                throw Exception::InputException(t, message);
/*}}}*/
            }
        } catch (std::out_of_range &e) {
            // Accessed an element of container returned by getParsed()
            // that did not exist. This would be a bug in this class (or
            // its parent). Keywords: bad parsing, outdated command
            // specification.
            std::string message = "out_of_range: ";
            message.append(e.what());
            _control.print(message);
            printErr(message);
        }
    }

/*}}}*/
}

// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
