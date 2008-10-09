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

#ifndef COMMANDPARSERDUMMY_H
#define COMMANDPARSERDUMMY_H

// INCLUDES/*{{{*/

#include <string>
#include <list>
#include <CommandParser/AbcCommandParser.hxx>

/*}}}*/

using CommandParser::param;
using CommandParser::command;
using CommandParser::commandMap;

/**
 * @class CommandParserDummy
 * @brief Dummy implementation of the ABC CommandParser::AbcCommandParser
 *
 * Inherits from the abstract base class @ref CommandParser::AbcCommandParser
 * and definines the abstract methods as "dummy" ones that do no "real" work but
 * are optimized for unit tests.
 */
class CommandParserDummy : public CommandParser::AbcCommandParser
{

  public:
    CommandParserDummy(const std::string &command);
    ~CommandParserDummy();

  protected:

  private:
    commandMap _createCommands() const;
};

// For the various test classes
typedef std::list<CommandParserDummy> parserList;
typedef std::list<std::string> commandList;


#endif // COMMANDPARSERDUMMY_H

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
