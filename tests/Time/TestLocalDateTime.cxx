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

#include <ctime>
#include <Time/LocalDateTime.hxx>
#include "TestLocalDateTime.hxx"

/*}}}*/

const time_t TestLocalDateTime::TIME = 1220562843;

void TestLocalDateTime::setUp()/*{{{*/
{
}

/*}}}*/
void TestLocalDateTime::tearDown()/*{{{*/
{
}

/*}}}*/
void TestLocalDateTime::testCtorTs()/*{{{*/
{
    Time::Timestamp ts;
    Time::LocalDateTime date(ts);
}

/*}}}*/
void TestLocalDateTime::testCtorInt()/*{{{*/
{
    Time::LocalDateTime date(2008, 9, 4, 23, 14, 3);
}

/*}}}*/
void TestLocalDateTime::testGetTimestamp()/*{{{*/
{
    Time::Timestamp ts(TestLocalDateTime::TIME);
    Time::LocalDateTime date(ts);
    CPPUNIT_ASSERT_EQUAL(TestLocalDateTime::TIME, date.getTimestamp().raw());
}

/*}}}*/
void TestLocalDateTime::testRaw()/*{{{*/
{
    Time::LocalDateTime date(2008, 9, 4, 23, 14, 3);
    const struct tm *tm = date.raw();
    // Some values may seem to be weird, see man ctime for this.
    CPPUNIT_ASSERT_EQUAL(108,  tm->tm_year);
    CPPUNIT_ASSERT_EQUAL(8,    tm->tm_mon);
    CPPUNIT_ASSERT_EQUAL(4,    tm->tm_mday);
    CPPUNIT_ASSERT_EQUAL(23,   tm->tm_hour);
    CPPUNIT_ASSERT_EQUAL(14,   tm->tm_min);
    CPPUNIT_ASSERT_EQUAL(3,    tm->tm_sec);
}

/*}}}*/

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
