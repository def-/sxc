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

#ifndef TESTOUTPUT_H
#define TESTOUTPUT_H

// INCLUDES/*{{{*/

#include <string>
#include <fstream>
#include <cppunit/extensions/HelperMacros.h>
#include "OutputDummy.hxx"

/*}}}*/

/**
 * @class TestOutput
 * @brief Testsuite for the File::OutputDummy class.
 */
class TestOutput : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(TestOutput);
    CPPUNIT_TEST(testInitialize);
    CPPUNIT_TEST(testOpen);
    CPPUNIT_TEST(testClose);
    CPPUNIT_TEST(testWrite);
    CPPUNIT_TEST_EXCEPTION(exceptClose, std::ofstream::failure);
  CPPUNIT_TEST_SUITE_END();

  public:
    static const std::string path;

    void setUp();
    void tearDown();

    // Public interface of OutputBase or OutputDummy:
    void testInitialize();
    void testOpen();
    void testWrite();
    void testClose();
    void exceptClose();

  protected:

  private:
    OutputDummy *_output;
};

#endif // TESTOUTPUT_H

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
