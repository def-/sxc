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

#ifndef TESTNOCOMMANDPARSER_H
#define TESTNOCOMMANDPARSER_H

// INCLUDES/*{{{*/

#include <cppunit/extensions/HelperMacros.h>
#include <list>
#include "CommandParserDummy.hxx"
#include <Exception/InputException.hxx>

/*}}}*/

/**
 * @class TestNoCommandParser
 * @brief Testsuite for the CommandParser::AbcCommandParser class.
 * @author Andreas Waidler
 *
 * Uses an object of the dummy child class CommandParserDummy to test
 * AbcCommandParser for functionality.
 */
class TestNoCommandParser : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestNoCommandParser);
        CPPUNIT_TEST_EXCEPTION(testParse, Exception::InputException);
        CPPUNIT_TEST_EXCEPTION(testGetName, Exception::InputException);
        CPPUNIT_TEST_EXCEPTION(testGetParameterString, Exception::InputException);
        CPPUNIT_TEST_EXCEPTION(testGetParsed, Exception::InputException);
    CPPUNIT_TEST_SUITE_END();

    public:
        TestNoCommandParser();

        void setUp();
        void tearDown();

        // Public interface of CommandParser:
        void testParse();
        void testGetName();
        void testGetParameterString();
        void testGetParsed();

    protected:

    private:
        parserList _parsers;
        commandList _commands;
};

#endif // TESTNOCOMMANDPARSER_H

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
