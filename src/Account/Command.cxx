#line 2 "sxc:Account/Command.cxx"
// LICENSE/*{{{*/
/*
  sxc - Simple Xmpp Client
  Copyright (C) 2008 Dennis Felsing, Andreas Waidler

  Permission to use, copy, modify, and/or distribute this software for any
  purpose with or without fee is hereby granted, provided that the above
  copyright notice and this permission notice appear in all copies.

  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
/*}}}*/

// INCLUDES/*{{{*/

#ifdef HAVE_CONFIG_H
# include <config.hxx>
#endif

#include <stdexcept>
#include <string>
#include <sstream>
#include <deque>
#include <map>

#include <Account/Command.hxx>
#include <Account/Account.hxx>
#include <Account/Roster.hxx>
#include <CommandParser/Exception/InvalidCommand.hxx>

#include <libsxc/Logger.hxx>
#include <libsxc/Exception/Exception.hxx>
#include <libsxc/Exit/Code.hxx>

/*}}}*/

using libsxc::Error;

using CommandParser::commandMap;
using CommandParser::command;
using CommandParser::param;

namespace Account
{
  Command::Command(Account &account, const std::string &command)/*{{{*/
  : AbcCommandParser(command),
    _account(account)
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

      if ("ack" == name) {/*{{{*/
        _account.acknowledgeSubscription(parsed.at(1));
/*}}}*/
      } else if ("dec" == name) {/*{{{*/
        _account.declineSubscription(parsed.at(1));
/*}}}*/
      } else if ("add" == name) {/*{{{*/
        _account.addContact(parsed.at(1));
/*}}}*/
      } else if ("del" == name) {/*{{{*/
        _account.removeContact(parsed.at(1));
/*}}}*/
      } else if ("msg" == name) {/*{{{*/
        _account.sendMessage(parsed.at(1), parsed.at(2));
/*}}}*/
      } else if ("pgp" == name) {/*{{{*/
        const std::string action = parsed.at(1);
        if ("chk" == action) {
        } else if ("dec" == action) {
        } else if ("enc" == action) {
        } else if ("sig" == action) {
        } else {
          std::string message = "Unknown parameter '"
                    + action + "' for command 'pgp'.";
          throw CommandParser::Exception::InvalidCommand(message.c_str());
        }
        // FIXME add pgp
        throw libsxc::Exception::Exception("Unimplemented.", libsxc::Exit::General);
/*}}}*/
      } else if ("pwd" == name) {/*{{{*/
        _account.setPassphrase(parsed.at(1));
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
          _account.disconnect();
          return;
        } else {
          std::string message = "Not a state to :set : '"
                    + presenceStr + "'";
          throw CommandParser::Exception::InvalidCommand(message.c_str());
        }

        if (2 == parsed.size())
          _account.setPresence(presence);
        else
          _account.setPresence(presence, parsed.at(2));
/*}}}*/
      } else if ("pri" == name) {/*{{{*/
        int priority;

        std::istringstream ss;
        ss.str(parsed.at(1));
        ss >> priority;

        if (priority > 127 || priority < -128) {
          std::string message =
            "Invalid parameter \"" + parsed.at(1) +
            "\" for command \"pri\". Has to be a number between " +
            "-128 and 127";
          throw CommandParser::Exception::InvalidCommand(message.c_str());
        }

        _account.setPriority(priority);
/*}}}*/
      } else if ("sub" == name) {/*{{{*/
        _account.subscribe(parsed.at(1), parsed.at(2));
/*}}}*/
      } else if ("usc" == name) {/*{{{*/
        _account.unsubscribe(parsed.at(1), parsed.at(2));
/*}}}*/
      } else {/*{{{*/
        std::string message = "Unknown name: " + name;
        throw CommandParser::Exception::InvalidCommand(message.c_str());
/*}}}*/
      }
    } catch (std::out_of_range &e) {
      // Accessed an element of container returned by getParsed()
      // that did not exist. This would be a bug in this class (or
      // its parent). Keywords: bad parsing, outdated command
      // specification.
      std::string message = "out_of_range: ";
      message.append(e.what());
      //_account.print(message); // FIXME
      LOG<Error>(message);
    }
  }

/*}}}*/
}

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
