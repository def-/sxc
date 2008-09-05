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

#ifndef TESTLOCALDATETIME_H
#define TESTLOCALDATETIME_H

// INCLUDES/*{{{*/

#include <ctime>
#include <cppunit/extensions/HelperMacros.h>

/*}}}*/

class TestLocalDateTime : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestLocalDateTime);
        CPPUNIT_TEST(testCtorTs);
        CPPUNIT_TEST(testCtorInt);
        CPPUNIT_TEST(testGetTimestamp);
        CPPUNIT_TEST(testRaw);
    CPPUNIT_TEST_SUITE_END();

    public:
        static const time_t TIME;

        void setUp();
        void tearDown();

        void testCtorTs();
        void testCtorInt();
        void testGetTimestamp();
        void testRaw();

    protected:

    private:
};

#endif // TESTLOCALDATETIME_H

// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
