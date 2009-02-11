#line 2 "sxc:Command/Parser.cxx"
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

// INCLUDE/*{{{*/

#ifdef HAVE_CONFIG_H
# include <config.hxx>
#endif

#include <Command/Parser.hxx>

#include <Command/Factory.hxx>
#include <Command/Command.hxx>
#include <Command/Exception/CouldNotParse.hxx>
#include <Command/Exception/NotParsed.hxx>
#include <Command/utilities.hxx>

#include <libsxc/Debug/Logger.hxx>
#include <libsxc/Exception/RuntimeError.hxx>
#include <libsxc/Exception/Underflow.hxx>

/*}}}*/

namespace Command
{
  std::string Parser::substr(/*{{{*/
    const std::string& str, std::string::iterator pos)
  {
    std::string buf;
    for ( ; str.end() != pos; ++pos) {
      buf.push_back(*pos);
    }
    return buf;
  }

/*}}}*/

  Parser::Parser(const std::string& input, const Factory& factory)/*{{{*/
  : _input(input)
  , _factory(&factory)
  , _command(NULL)
  {
  }

/*}}}*/
  Parser::~Parser()/*{{{*/
  {
    _dispose();
  }

/*}}}*/
  const std::string& Parser::getInput() const/*{{{*/
  {
    return _input;
  }

/*}}}*/
  Command& Parser::parse()/*{{{*/
  {
    try {
      // Free any allocated memory before overwriting the pointers.
      _dispose();

      // Using an iterator to traverse the string.
      std::string::iterator pos = _input.begin();

      if (_input.end() == pos)
        throw libsxc::Exception::RuntimeError("Empty input.");

      if (':' != *pos) // TODO: Prefix as parameter or sth like that.
        throw libsxc::Exception::RuntimeError("No command prefix found.");

      // Get the command name.

      std::string buf;
      // Until end of string or end of word (command name) is reached.
      for (++pos; pos != _input.end() && *pos != ' '; ++pos) {
        buf.push_back(*pos);
      }
      _command = _factory->createCommand(buf);
      _command->add(buf);

      // Command created. Check whether it shall get some arguments and, if not,
      // is in fact already complete.
      if (_input.end() == pos) {
        if (_command->isComplete())
          return *_command;
        throw libsxc::Exception::RuntimeError("All arguments missing.");
      }

      // There are some arguments for this command. Check whether it expects any
      if (_command->isComplete())
        throw libsxc::Exception::RuntimeError(
          "Passed arguments for an empty complete command.");
      // TODO: Implement and check for _cmd->hasOptional().

      // Parse the arguments.
      // Iterate over the characters while checking whether they shall be
      // treated specially.

      buf.assign("");
      for (++pos; pos != _input.end(); ++pos) {
        // Whitespaces delimit arguments.
        if (' ' != *pos) {
          buf.push_back(*pos);
        } else {
          if (buf.empty())
            continue;

          LOG("Whitespace found. Argument is " + buf);
          if (!_command->isComplete()) {
            LOG("Add argument since command is incomplete.");
            _command->add(buf);
            buf.assign("");
          // else if (_command->hasOptional()) // TODO: Impl such a method
            // Add rest of input as one parameter.
            // // see below but use add() not append()
          } else {
            // Command fully complete. Append remaining input to last parameter.
            LOG("Command is complete, append it to the end.");
            std::string rest(buf);
            rest.push_back(' ');
            rest.append(substr(_input, pos));
            append(*_command, rest);
            buf.assign("");
            break;
          }
        }
      }
      LOG("End of input. Add remaining contents of buffer as new argument.");
      if (!buf.empty())
        _command->add(buf);
      // The following check is done by the command itsself and may decrease
      // flexibility if implemented here.
      // if (!_command->isComplete())
        // throw libsxc::Exception::Underflow("Arguments missing.");

      return *_command;
    } catch (std::exception& e) {
      throw Exception::CouldNotParse(_input.c_str(), e);
    }
  }

/*}}}*/
  Command& Parser::getCommand() const/*{{{*/
  {
    if (NULL == _command) {
      throw Exception::NotParsed();
    }

    return *_command;
  }

/*}}}*/
  void Parser::_dispose()/*{{{*/
  {
    if (NULL == _command) {
      delete _command;
    }
  }

/*}}}*/
}

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
