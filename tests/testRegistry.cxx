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
