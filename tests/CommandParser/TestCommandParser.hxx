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

#ifndef TESTINPUTPARSER_H
#define TESTINPUTPARSER_H

// INCLUDES/*{{{*/

#include <cppunit/extensions/HelperMacros.h>
#include <list>
#include <CommandParser/AbcCommandParser.hxx>

/*}}}*/

/**
 * @class TestCommandParser
 * @brief Testsuite for the CommandParser::AbcCommandParser class.
 * @author Andreas Waidler
 *
 * Uses an object of the dummy child class CommandParserDummy to test
 * AbcCommandParser for functionality.
 */
class TestCommandParser : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestCommandParser);
        CPPUNIT_TEST(testLifecycle);
        CPPUNIT_TEST(testParse);
        CPPUNIT_TEST(testGetName);
        CPPUNIT_TEST(testGetParameterString);
        CPPUNIT_TEST(testGetParsed);
        CPPUNIT_TEST(failParseNoCommand);
        CPPUNIT_TEST(failParseInvCommand);
        CPPUNIT_TEST(failParseInvParam);
    CPPUNIT_TEST_SUITE_END();

    public:
        TestCommandParser();

        void setUp();
        void tearDown();

        // Public interface of CommandParser:
        void testLifecycle();
        void testParse();
        void testGetName();
        void testGetParameterString();
        void testGetParsed();
        void failParseNoCommand();
        void failParseInvCommand();
        void failParseInvParam();

    protected:

    private:
        CommandParser::AbcCommandParser *_parser;
        std::list<std::string> _noCommands;
        std::list<std::string> _goodCommands;
        std::list<std::string> _invalidCommands;
        std::list<std::string> _invalidParamCommands;
};

#endif // TESTINPUTPARSER_H

// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
