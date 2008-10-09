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

#ifndef TESTINPUT_H
#define TESTINPUT_H

// INCLUDES/*{{{*/

#include <sys/stat.h>

#include <string>
#include <Exception/FileInputException.hxx>
#include <cppunit/extensions/HelperMacros.h>
#include "InputDummy.hxx"

/*}}}*/

/**
 * @class TestInput
 * @brief Testsuite for the File::InputDummy class.
 */
class TestInput : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestInput);
        CPPUNIT_TEST(testCreate);
        CPPUNIT_TEST_EXCEPTION(exceptCreateExist,
                               Exception::FileInputException);
        CPPUNIT_TEST(testValidate);
        CPPUNIT_TEST_EXCEPTION(exceptValidateMissing,
                               Exception::FileInputException);
        CPPUNIT_TEST_EXCEPTION(exceptValidate200,
                               Exception::FileInputException);
        CPPUNIT_TEST_EXCEPTION(exceptValidate400,
                               Exception::FileInputException);
        CPPUNIT_TEST_EXCEPTION(exceptValidate604,
                               Exception::FileInputException);
        CPPUNIT_TEST_EXCEPTION(exceptValidate640,
                               Exception::FileInputException);
        CPPUNIT_TEST_EXCEPTION(exceptValidateBad,
                               Exception::FileInputException);
        CPPUNIT_TEST(testClose);
        CPPUNIT_TEST(testListen);
        CPPUNIT_TEST(testListenClose);
        CPPUNIT_TEST(testReadSimple);
        CPPUNIT_TEST(testReadNL);
        CPPUNIT_TEST(testReadNull);
        CPPUNIT_TEST(testReadTrailNull);
        CPPUNIT_TEST(testReadLeadNull);
    CPPUNIT_TEST_SUITE_END();

    public:
        static const std::string fifoPath;

        void setUp();
        void tearDown();

        // Protected methods of InputBase:
        void testCreate();
        void exceptCreateExist();
        void testValidate();
        void exceptValidateMissing();
        void exceptValidate200();
        void exceptValidate400();
        void exceptValidate604();
        void exceptValidate640();
        void exceptValidateBad();
        void testClose();
        void testReadSimple();
        void testReadNL();
        void testReadNull();
        void testReadTrailNull();
        void testReadLeadNull();

        // Public interface of InputBase or InputDummy:
        void testListen();
        void testListenClose();

        // Helper methods:
        void exceptValidateChmod(mode_t mode);

    protected:

    private:
        InputDummy *_inputDummy;
};

#endif // TESTINPUT_H

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
