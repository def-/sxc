#line 2 "sxc:Contact/Command.cxx"
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

#include <Contact/Command.hxx>
#include <Exception/InputException.hxx>
#include <libsxc/Exception/Exception.hxx>
#include <Contact/Contact.hxx>
#include <Account/Account.hxx>
#include <Account/Roster.hxx>
#include <libsxc/Logger.hxx>

/*}}}*/

using libsxc::Error;

using CommandParser::commandMap;
using CommandParser::command;
using CommandParser::param;

namespace Contact
{
  Command::Command(/*{{{*/
    Contact &contact,
    const std::string &command)
  : AbcCommandParser(command)
  , _contact(contact)
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

      if ("ack" == name) {/*{{{*/
        _contact.acknowledgeSubscription();
/*}}}*/
      } else if ("dec" == name) {/*{{{*/
        _contact.declineSubscription();
/*}}}*/
      } else if ("add" == name) {/*{{{*/
        _contact.add();
/*}}}*/
      } else if ("del" == name) {/*{{{*/
        _contact.remove();
/*}}}*/
      } else if ("msg" == name) {/*{{{*/
        _contact.sendMessage(parsed.at(1));
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
        _contact.subscribe(parsed.at(1));
/*}}}*/
      } else if ("usc" == name) {/*{{{*/
        _contact.unsubscribe(parsed.at(1));
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
      //_account.print(message); // FIXME
      LOG<Error>(message);
    }
  }

/*}}}*/
}

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
