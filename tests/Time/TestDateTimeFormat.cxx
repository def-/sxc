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
#include <string>
#include <sstream>
#include <Time/Timestamp.hxx>
#include <Time/LocalDateTime.hxx>
#include <Time/DateTimeFormat.hxx>
#include "TestDateTimeFormat.hxx"

/*}}}*/

const time_t TestDateTimeFormat::TIME = 1220562843;

void TestDateTimeFormat::setUp()/*{{{*/
{
}

/*}}}*/
void TestDateTimeFormat::tearDown()/*{{{*/
{
}

/*}}}*/
void TestDateTimeFormat::testCtor()/*{{{*/
{
    Time::LocalDateTime date(Time::Timestamp(TestDateTimeFormat::TIME));
    Time::DateTimeFormat formatter(&date);
}

/*}}}*/
void TestDateTimeFormat::testFormat()/*{{{*/
{
    Time::LocalDateTime date(Time::Timestamp(TestDateTimeFormat::TIME));
    Time::DateTimeFormat formatter(&date);
    CPPUNIT_ASSERT_EQUAL(std::string("2008-09-04"), formatter.format("%F"));

    std::stringstream ssTs;
    ssTs << TestDateTimeFormat::TIME;
    CPPUNIT_ASSERT_EQUAL(ssTs.str(), formatter.format("%s"));
}

/*}}}*/

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
