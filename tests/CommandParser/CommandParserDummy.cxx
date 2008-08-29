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

#include <string>
#include <CommandParser/AbcCommandParser.hxx>
#include "CommandParserDummy.hxx"

/*}}}*/

CommandParserDummy::CommandParserDummy(std::string input)/*{{{*/
: AbcCommandParser(input)
{
}

/*}}}*/
CommandParserDummy::~CommandParserDummy()/*{{{*/
{
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

// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
