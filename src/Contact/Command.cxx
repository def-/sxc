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

#include <stdexcept>
#include <string>
#include <sstream>
#include <deque>
#include <map>

#include <Contact/Command.hxx>
#include <Exception/InputException.hxx>
#include <libsxc/Exception/Exception.hxx>
#include <Contact/Contact.hxx>
#include <Control/Control.hxx>
#include <Control/Roster.hxx>

/*}}}*/

using CommandParser::commandMap;
using CommandParser::command;
using CommandParser::param;

namespace Contact
{
    Command::Command(/*{{{*/
        Control::Control &control,
        Contact &contact,
        const std::string &command)
    : AbcCommandParser(command),
      _control(control),
      _contact(contact)
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

        it = map.insert(it, command("ack", param(0, false)));
        it = map.insert(it, command("dec", param(0, false)));
        it = map.insert(it, command("add", param(0, false)));
        it = map.insert(it, command("del", param(0, false)));
        it = map.insert(it, command("msg", param(1, false)));
        it = map.insert(it, command("pgp", param(1, true)));
        it = map.insert(it, command("sub", param(0, true)));
        it = map.insert(it, command("usc", param(0, true)));

        return map;
    }

/*}}}*/
    void Command::execute()/*{{{*/
    {
        // TODO
        // FIXME Catch exceptions.
        try {
            parse();
            const std::deque<std::string> parsed = getParsed();
            const std::string name = parsed.at(0);

            Control::Roster &roster = _control.getRoster();

            if ("ack" == name) {/*{{{*/
                roster.acknowledgeSubscription(_contact.getJid().bare());
/*}}}*/
            } else if ("dec" == name) {/*{{{*/
                roster.declineSubscription(_contact.getJid().bare());
/*}}}*/
            } else if ("add" == name) {/*{{{*/
                roster.addContact(_contact.getJid().bare());
/*}}}*/
            } else if ("del" == name) {/*{{{*/
                roster.removeContact(_contact.getJid().bare());
/*}}}*/
            } else if ("msg" == name) {/*{{{*/
                _contact.sendMessage(
                    _contact.getJid().bare(),
                    parsed.at(1));
/*}}}*/
            } else if ("pgp" == name) {/*{{{*/
                const std::string action = parsed.at(1);
                // FIXME add pgp
                if ("key" == action) {
                } else if ("on" == action) {
                } else if ("off" == action) {
                } else {
                    libsxc::Exception::Type type =
                        libsxc::Exception::InvalidCommand;
                    std::string message = "Unknown parameter '"
                                        + action + "' for command 'pgp'.";
                    throw Exception::InputException(type, message);
                }
                throw Exception::InputException(
                    libsxc::Exception::General, "Unimplemented.");
/*}}}*/
            } else if ("sub" == name) {/*{{{*/
                roster.subscribe(_contact.getJid().bare(), parsed.at(1));
/*}}}*/
            } else if ("usc" == name) {/*{{{*/
                roster.unsubscribe(_contact.getJid().bare(), parsed.at(1));
/*}}}*/
            } else {/*{{{*/
                libsxc::Exception::Type t = libsxc::Exception::InvalidCommand;
                std::string message = "Unknown name: " + name;
                throw Exception::InputException(t, message);
            }/*}}}*/
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
