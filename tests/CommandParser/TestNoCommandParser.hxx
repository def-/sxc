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

#ifndef TESTNOCOMMANDPARSER_H
#define TESTNOCOMMANDPARSER_H

// INCLUDES/*{{{*/

#include <cppunit/extensions/HelperMacros.h>
#include <list>
#include "CommandParserDummy.hxx"

#include <libsxc/Exception/Exception.hxx>

/*}}}*/

/**
 * @class TestNoCommandParser
 * @brief Testsuite for the CommandParser::AbcCommandParser class.
 *
 * Uses an object of the dummy child class CommandParserDummy to test
 * AbcCommandParser for functionality.
 */
class TestNoCommandParser : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(TestNoCommandParser);
    CPPUNIT_TEST_EXCEPTION(testParse, libsxc::Exception::Exception);
    CPPUNIT_TEST_EXCEPTION(testGetName, libsxc::Exception::Exception);
    CPPUNIT_TEST_EXCEPTION(testGetParameterString, libsxc::Exception::Exception);
    CPPUNIT_TEST_EXCEPTION(testGetParsed, libsxc::Exception::Exception);
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
