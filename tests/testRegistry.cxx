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

// INCLUDE/*{{{*/

#include <cppunit/extensions/HelperMacros.h>

#include <File/TestInput.hxx>
#include <File/TestOutput.hxx>
#include <CommandParser/TestCommandParser.hxx>
#include <CommandParser/TestNoCommandParser.hxx>
#include <CommandParser/TestInvalidCommandParser.hxx>
#include <Time/TestDateTimeFormat.hxx>
#include <Time/TestIsoDateTimeFormat.hxx>
#include <Time/TestLocalDateTime.hxx>
#include <Time/TestTimestamp.hxx>

/*}}}*/

// Registering all unit tests here, to make them easier to disable and enable.

CPPUNIT_TEST_SUITE_REGISTRATION(TestInput);
CPPUNIT_TEST_SUITE_REGISTRATION(TestOutput);
CPPUNIT_TEST_SUITE_REGISTRATION(TestCommandParser);
CPPUNIT_TEST_SUITE_REGISTRATION(TestNoCommandParser);
CPPUNIT_TEST_SUITE_REGISTRATION(TestInvalidCommandParser);
CPPUNIT_TEST_SUITE_REGISTRATION(TestTimestamp);
CPPUNIT_TEST_SUITE_REGISTRATION(TestLocalDateTime);
CPPUNIT_TEST_SUITE_REGISTRATION(TestDateTimeFormat);
CPPUNIT_TEST_SUITE_REGISTRATION(TestIsoDateTimeFormat);

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
