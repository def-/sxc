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

// #include <cstdio>
// #include <unistd.h>

#include <algorithm>
#include <iostream>
#include <string>
#include <deque>
#include <list>

#include <cppunit/Exception.h>
#include <Exception/InputException.hxx>
#include <libsxc/Exception/Type.hxx>
#include "TestInvalidCommandParser.hxx"
#include "CommandParserDummy.hxx"

/*}}}*/

TestInvalidCommandParser::TestInvalidCommandParser()/*{{{*/
{
    /* These specifications have been set in CommandParserDummy:
    it = map.insert(it, command("one", param(1, false)));
    it = map.insert(it, command("1++", param(1, true)));
    it = map.insert(it, command("two", param(2, false)));
    it = map.insert(it, command("2++", param(2, true)));
    it = map.insert(it, command("thr", param(3, false)));
    it = map.insert(it, command("3++", param(3, true)));
    it = map.insert(it, command("fou", param(4, false)));
    it = map.insert(it, command("4++", param(4, true)));
    */

    // Some invalid commands.
    _commands.push_back(":foo");
    _commands.push_back(":bar");
    _commands.push_back(":foo bar");
    _commands.push_back(":f o o b a r");
    _commands.push_back(":");

    // Some commands that have an invalid amount of parameters.
    _commands.push_back(":two");
    _commands.push_back(":fou one");
    _commands.push_back(":fou one two");
    _commands.push_back(":fou one two three");
}

/*}}}*/
void TestInvalidCommandParser::setUp()/*{{{*/
{
    commandList::iterator it = _commands.begin();
    for ( ; it != _commands.end(); ++it) {
        _parsers.push_back(CommandParserDummy(*it));
    }
}

/*}}}*/
void TestInvalidCommandParser::tearDown()/*{{{*/
{
    _parsers.clear();
}

/*}}}*/
void TestInvalidCommandParser::testParse()/*{{{*/
{
    parserList::iterator it = _parsers.begin();
    for ( ; it != _parsers.end(); ++it) {
        it->parse();
    }
}

/*}}}*/
void TestInvalidCommandParser::testGetName()/*{{{*/
{
    parserList::iterator it = _parsers.begin();
    for ( ; it != _parsers.end(); ++it) {
        it->parse();
        const std::string name = it->getName();
        if ("one" != name && "1++" != name && "two" != name && "2++" != name
        && "thr" != name && "3++" != name && "fou" != name && "4++" != name)
            CPPUNIT_FAIL("Unknown command name: '" + name + "'");
    }
}

/*}}}*/
void TestInvalidCommandParser::testGetParameterString()/*{{{*/
{
    parserList::iterator it = _parsers.begin();
    for ( ; it != _parsers.end(); ++it) {
        it->parse();
        const std::string name   = it->getName();
        const std::string params = it->getParameterString();
        if (name == "one" || name == "1++" || name == "two" || name == "2++") {
            CPPUNIT_ASSERT_EQUAL(std::string("foo bar"), params);
        } else if (name == "thr" || name == "3++" || name == "fou") {
            CPPUNIT_ASSERT_EQUAL(std::string("foo bar rab oof"), params);
        } else if (name == "4++") {
            CPPUNIT_ASSERT_EQUAL(std::string("foo bar rab oof foobar raboof"),
                params);
        } else {
            CPPUNIT_FAIL("Unknown command name: '" + name + "'");
        }
    }
}

/*}}}*/
void TestInvalidCommandParser::testGetParsed()/*{{{*/
{
    parserList::iterator it = _parsers.begin();
    for ( ; it != _parsers.end(); ++it) {
        it->parse();
        std::deque<std::string> parsed = it->getParsed();
        const std::string name = parsed.at(0);
        // Amount of parameters:
        const int cArgs = (int) parsed.size() - 1;
        if (name == "one") {
            CPPUNIT_ASSERT_EQUAL(1, cArgs);
            CPPUNIT_ASSERT_EQUAL(std::string("foo bar"), parsed.at(1));
        } else if (name == "1++" || name == "two" || name == "2++") {
            CPPUNIT_ASSERT_EQUAL(2, cArgs);
            CPPUNIT_ASSERT_EQUAL(std::string("foo"), parsed.at(1));
            CPPUNIT_ASSERT_EQUAL(std::string("bar"), parsed.at(2));
        } else if (name == "thr") {
            CPPUNIT_ASSERT_EQUAL(3, cArgs);
            CPPUNIT_ASSERT_EQUAL(std::string("foo"), parsed.at(1));
            CPPUNIT_ASSERT_EQUAL(std::string("bar"), parsed.at(2));
            CPPUNIT_ASSERT_EQUAL(std::string("rab oof"), parsed.at(3));
        } else if (name == "3++" || name == "fou") {
            CPPUNIT_ASSERT_EQUAL(4, cArgs);
            CPPUNIT_ASSERT_EQUAL(std::string("foo"), parsed.at(1));
            CPPUNIT_ASSERT_EQUAL(std::string("bar"), parsed.at(2));
            CPPUNIT_ASSERT_EQUAL(std::string("rab"), parsed.at(3));
            CPPUNIT_ASSERT_EQUAL(std::string("oof"), parsed.at(4));
        } else if (name == "4++") {
            CPPUNIT_ASSERT_EQUAL(5, cArgs);
            CPPUNIT_ASSERT_EQUAL(std::string("foo"), parsed.at(1));
            CPPUNIT_ASSERT_EQUAL(std::string("bar"), parsed.at(2));
            CPPUNIT_ASSERT_EQUAL(std::string("rab"), parsed.at(3));
            CPPUNIT_ASSERT_EQUAL(std::string("oof"), parsed.at(4));
            CPPUNIT_ASSERT_EQUAL(std::string("foobar raboof"), parsed.at(5));
        } else {
            CPPUNIT_FAIL("Unknown command name: '" + name + "'");
        }
    }
}

/*}}}*/

// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
