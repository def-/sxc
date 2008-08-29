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

#ifndef TESTINPUT_H
#define TESTINPUT_H

// INCLUDES/*{{{*/

#include <string>

#include <cppunit/extensions/HelperMacros.h>

#include "InputDummy.hxx"

/*}}}*/

/**
 * @class TestInput
 * @brief Testsuite for the File::InputDummy class.
 * @author Andreas Waidler
 */
class TestInput : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestInput);
        CPPUNIT_TEST(testCreate);
        CPPUNIT_TEST(failCreateExist);
        CPPUNIT_TEST(testValidate);
        CPPUNIT_TEST(testValidateMissing);
        CPPUNIT_TEST(testValidateBad);
        CPPUNIT_TEST(testClose);
        CPPUNIT_TEST(testListenClose);
        CPPUNIT_TEST(testWrite);
    CPPUNIT_TEST_SUITE_END();

    public:
        static const std::string fifoPath;

        void setUp();
        void tearDown();

        // Protected methods of InputBase:
        void testCreate();
        void failCreateExist();
        void testValidate();
        void testValidateMissing();
        void testValidateBad();
        void testClose();

        // Public interface of InputBase or InputDummy:
        void testListenClose();
        void testWrite();

    protected:

    private:
        InputDummy *_inputDummy;
};

#endif // TESTINPUT_H

// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker


