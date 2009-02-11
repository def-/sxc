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

#include "Mock/NoOp.hxx"
#include "Mock/OneParamSwitch.hxx"

#include <cppunit/extensions/HelperMacros.h>

/*}}}*/

#ifndef TESTCOMMAND_HXX
#define TESTCOMMAND_HXX

class TestCommand : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(TestCommand);
    CPPUNIT_TEST(testLifecycle);
    CPPUNIT_TEST(testAdd);
    CPPUNIT_TEST(testAmountAdded);
    CPPUNIT_TEST(testOrderAdded);
    CPPUNIT_TEST(testSet);
    CPPUNIT_TEST(testAmountSet);
    CPPUNIT_TEST(testOrderSet);
    CPPUNIT_TEST(testNoOpComplete);
    CPPUNIT_TEST(testComplete);
    CPPUNIT_TEST(testExecute);
  CPPUNIT_TEST_SUITE_END();

  public:
    TestCommand();

    void setUp();
    void tearDown();

    // void testLifecycle();/*{{{*/

    /**
     * @brief Tests the lifecycle of the command objects.
     *
     * Is, in fact, no-op since the objects are created and destroyed in
     * setUp() and tearDown().
     */
    void testLifecycle() {}

/*}}}*/
    // void testAdd();/*{{{*/

    /**
     * @brief Tests add().
     */
    void testAdd();

/*}}}*/
    // void testAmountAdded();/*{{{*/

    /**
     * @brief Checks whether the amount of added arguments is correct.
     *
     * Adds some arguments to a noop command and check the resulting length.
     */
    void testAmountAdded();

/*}}}*/
    // void testOrderAdded();/*{{{*/

    /**
     * @brief Checks the resulting order created by add().
     *
     * Adds some arguments to a noop command and check the resulting order.
     */
    void testOrderAdded();

/*}}}*/
    // void testSet();/*{{{*/

    /**
     * @brief Tests set().
     */
    void testSet();

/*}}}*/
    // void testAmountSet();/*{{{*/

    /**
     * @brief Checks whether the amount of added arguments is correct.
     *
     * Sets some arguments to a noop command and check the resulting length.
     */
    void testAmountSet();

/*}}}*/
    // void testOrderSet();/*{{{*/

    /**
     * @brief Checks the resulting order created by set().
     *
     * Sets some arguments to a noop command and check the resulting order.
     */
    void testOrderSet();

/*}}}*/
    // void testNoOpComplete();/*{{{*/

    /**
     * @brief Tests isComplete() for a noop command.
     *
     * On the noop command, isComplete() shall always be false.
     */
    void testNoOpComplete();

/*}}}*/
    // void testComplete();/*{{{*/

    /**
     * @brief Tests if isComplete() is set correctly.
     *
     * This needs an object derived from Command::Command and calling
     * setComplete() in one of the event handlers.
     */
    void testComplete();

/*}}}*/
    // void testExecute();/*{{{*/

    /**
     * @brief Checks whether operator() does call _execute().
     */
    void testExecute();

/*}}}*/

  private:
    Mock::NoOp* _noop;
    Mock::OneParamSwitch* _ops;
};

#endif // TESTCOMMAND_HXX

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
