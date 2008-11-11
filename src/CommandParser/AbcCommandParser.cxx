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

#include <sstream>
#include <string>
#include <deque>
#include <map>

#include <CommandParser/AbcCommandParser.hxx>
#include <Exception/InputException.hxx>

#include <libsxc/Logger.hxx>

/*}}}*/

using libsxc::Debug;

namespace CommandParser
{
  commandMap AbcCommandParser::_commands;
  AbcCommandParser::AbcCommandParser(const std::string &command)/*{{{*/
  : _command(command),
    _isParsed(false)
  {
  }

/*}}}*/
  AbcCommandParser::~AbcCommandParser()/*{{{*/
  {
  }

/*}}}*/
  void AbcCommandParser::parse()/*{{{*/
  {
    if (_isParsed)
      throw Exception::InputException(libsxc::Exception::InvalidUsage, "already parsed");

    // Check for proper formatting
    if (AbcCommandParser::_commandPrefix != _command.at(0)) {
      std::string msg = _command; // FIXME: Exceptions have to take const parameters!
      throw Exception::InputException(libsxc::Exception::NoCommand, msg);
    }
    if (4 != _command.find(' ')) {
      std::string msg = _command; // FIXME: Exceptions have to take const parameters!
      throw Exception::InputException(libsxc::Exception::InvalidCommand, msg);
    }
    // Properly formatted, may be a command. Start slicing it.
    _commandName = _command.substr(1, 3);
    _parameters  = _command.substr(5);

    // Get specifications for this command.
    commandMap commands = _getCommands();
    commandMap::iterator it = commands.find(_commandName);
    if (commands.end() == it) {
      // Invalid command. Input was only formatted like a command.
      std::string msg = _command; // FIXME: Exceptions have to take const parameters!
      throw Exception::InputException(libsxc::Exception::InvalidCommand, msg);
    }

    _parsed.push_back(_commandName);

    // Delimites the parameters.
    size_t delimiter;
    // Contains all parameters that have not yet been sliced.
    std::string paramsLeft = _parameters;

    {
      std::stringstream msg;
      msg << "entering parser loop for \""  + _command + "\", using "
        << ( it->second.first + (short) it->second.second )
        << " cycles.\n";
      LOG<Debug>(msg.str());
    }

    // Stops when the mandatory amount of parameters has been
    // handled.
    for (unsigned short i = 1;
    i < it->second.first + (short) it->second.second;
    ++i) {
      // Find end of current parameter:
      delimiter = paramsLeft.find(' ');
      if (std::string::npos == delimiter) {
        LOG<Debug>("Not found in \"" + paramsLeft + "\"\n");

        // Delimiter not found -> only one parameter left.
        if (i == it->second.first) // No problem, last one was optional.
          break;
        std::string msg = _command; // FIXME: Exceptions have to take const parameters!
        // FIXME: Use InvalidParameters below
        throw Exception::InputException(libsxc::Exception::InvalidCommand, msg);
      }

      // Extract the parameter and push it into the container.
      _parsed.push_back(paramsLeft.substr(0, (int)delimiter));

      LOG<Debug>(paramsLeft + '\n' + _parsed.back() + '~');

      // Remove parameter from the list of parameters left.
      paramsLeft = paramsLeft.substr((int)delimiter + 1);

      LOG<Debug>(paramsLeft + "\n----next cycle----\n");
    }
    LOG<Debug>("Out of loop, appending the last one.\n" + paramsLeft + '~');

    _parsed.push_back(paramsLeft);

    _isParsed = true;
  }

/*}}}*/
  const std::string &AbcCommandParser::get() const/*{{{*/
  {
    return _command;
  }

/*}}}*/
  const std::string &AbcCommandParser::getName() const/*{{{*/
  {
    if (_isParsed)
      return _commandName;

    std::string msg = _command; // FIXME: Exceptions have to take const parameters!
    throw Exception::InputException(libsxc::Exception::InvalidUsage, msg);
  }

/*}}}*/
  const std::string &AbcCommandParser::getParameterString() const/*{{{*/
  {
    if (_isParsed)
      return _parameters;

    std::string msg = _command; // FIXME: Exceptions have to take const parameters!
    throw Exception::InputException(libsxc::Exception::InvalidUsage, msg);
  }

/*}}}*/
  const std::deque<std::string> &AbcCommandParser::getParsed() const/*{{{*/
  {
    if (_isParsed)
      return _parsed;
    std::string msg = "Not parsed: " + _command;
    throw Exception::InputException(libsxc::Exception::InvalidUsage, msg);
  }

/*}}}*/
  const commandMap &AbcCommandParser::_getCommands() const/*{{{*/
  {
    if (AbcCommandParser::_commands.empty())
      AbcCommandParser::_commands = _createCommands();
    return AbcCommandParser::_commands;
  }

/*}}}*/
}

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
