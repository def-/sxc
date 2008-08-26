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

/* $Id$ */

// INCLUDE/*{{{*/

#include <string>
#include <gloox/jid.h>
#include <cppunit/extensions/HelperMacros.h>

#include <libsxc/Exception/OptionException.hxx>
#include <libsxc/Option/Parser.hxx>
#include <libsxc/Option/Option.hxx>
#include <libsxc/Option/OptionPort.hxx>

/*}}}*/


#ifndef TESTS_OPTION_OPTIONTEST_HXX
#define TESTS_OPTION_OPTIONTEST_HXX


class OptionTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(OptionTest);
        CPPUNIT_TEST(testCorrectParsing);
        CPPUNIT_TEST(testMissingObligatoryOption);
        CPPUNIT_TEST(testValueNotSet);
        CPPUNIT_TEST(testOptionSetMultipleTimes);
        CPPUNIT_TEST(testUnknownLongOption);
        CPPUNIT_TEST(testUnknownShortOption);
        CPPUNIT_TEST(testConflictingShortName);
        CPPUNIT_TEST(testConflictingLongName);
        CPPUNIT_TEST(testJids);
        CPPUNIT_TEST(testConvertType);
    CPPUNIT_TEST_SUITE_END();

    public:
        void setUp();
        void tearDown();

        void testCorrectParsing();
        void testMissingObligatoryOption();
        void testValueNotSet();
        void testOptionSetMultipleTimes();
        void testUnknownLongOption();
        void testUnknownShortOption();
        void testConflictingShortName();
        void testConflictingLongName();
        void testJids();
        void testConvertType();

    private:
        void doTestInvalidJid(std::string rawJid);
        void doTestValidJid(std::string rawJid);
        template<typename T> void doTestInvalidConvert(std::string rawValue);
        template<typename T> void doTestValidConvert(std::string rawValue);

        Option::Parser *_parser;
        Option::Option<bool> *_bool;
        Option::Option<bool> *_bool2;
        Option::Option<int> *_int;
        Option::Option<float> *_float;
        Option::Option<char> *_char;
        Option::Option<long> *_long;
        Option::Option<std::string> *_string;
        Option::Option<int> *_default;
        Option::Option<std::string> *_default2;
};


#endif // TESTS_OPTION_OPTIONTEST_HXX
// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
