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
#   include <config.hxx>
#endif
#include <print.hxx>
#include <iostream>

#include <string>
#include <CommandParser/AbcCommandParser.hxx>
#include "CommandParserDummy.hxx"

/*}}}*/

CommandParserDummy::CommandParserDummy(const std::string &command)/*{{{*/
: AbcCommandParser(command)
{
//#ifdef DEBUG
//    std::clog << "CommandParserDummy(" << command << ")" << std::endl;
//#endif
}

/*}}}*/
CommandParserDummy::~CommandParserDummy()/*{{{*/
{
//#ifdef DEBUG
//    std::clog << "~CommandParserDummy()" << std::endl;
//#endif
}

/*}}}*/
commandMap CommandParserDummy::_createCommands() const/*{{{*/
{
  commandMap map;
  commandMap::iterator it = map.begin();

  it = map.insert(it, command("one", param(1, false)));
  it = map.insert(it, command("1++", param(1, true)));
  it = map.insert(it, command("two", param(2, false)));
  it = map.insert(it, command("2++", param(2, true)));
  it = map.insert(it, command("thr", param(3, false)));
  it = map.insert(it, command("3++", param(3, true)));
  it = map.insert(it, command("fou", param(4, false)));
  it = map.insert(it, command("4++", param(4, true)));
  it = map.insert(it, command("fiv", param(5, false)));
  it = map.insert(it, command("5++", param(5, true)));
  it = map.insert(it, command("ten", param(10, false)));
  it = map.insert(it, command("10+", param(10, true)));

  return map;
}

/*}}}*/

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
