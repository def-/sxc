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
