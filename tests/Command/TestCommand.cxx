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

#include "TestCommand.hxx"

#include "Mock/NoOp.hxx"
#include "Mock/OneParamSwitch.hxx"

#include <Command/utilities.hxx>

/*}}}*/

TestCommand::TestCommand()/*{{{*/
: _noop(NULL)
, _ops(NULL)
{
}

/*}}}*/
void TestCommand::setUp()/*{{{*/
{
  _noop = new Mock::NoOp();
  _ops  = new Mock::OneParamSwitch();
}

/*}}}*/
void TestCommand::tearDown()/*{{{*/
{
  delete _noop;
  _noop = NULL;

  delete _ops;
  _ops = NULL;
}
/*}}}*/
void TestCommand::testAdd()/*{{{*/
{
  _noop->add("foo");
  _noop->add("bar");
  _noop->add("foobar");
  _noop->add("baz");
  _noop->add("barbaz");
  _noop->add("barfoo");
  _noop->add("raboof");
  _noop->add("rab");
  _noop->add("oof");
  _noop->add("oofrab");
}

/*}}}*/
void TestCommand::testAmountAdded()/*{{{*/
{
  testAdd();
  CPPUNIT_ASSERT_EQUAL(
    static_cast<unsigned int>(10), Command::countArguments(*_noop));
}

/*}}}*/
void TestCommand::testOrderAdded()/*{{{*/
{
  testAdd();
  CPPUNIT_ASSERT_EQUAL(std::string("foo"),    Command::argument(*_noop, 0));
  CPPUNIT_ASSERT_EQUAL(std::string("bar"),    Command::argument(*_noop, 1));
  CPPUNIT_ASSERT_EQUAL(std::string("foobar"), Command::argument(*_noop, 2));
  CPPUNIT_ASSERT_EQUAL(std::string("baz"),    Command::argument(*_noop, 3));
  CPPUNIT_ASSERT_EQUAL(std::string("barbaz"), Command::argument(*_noop, 4));
  CPPUNIT_ASSERT_EQUAL(std::string("barfoo"), Command::argument(*_noop, 5));
  CPPUNIT_ASSERT_EQUAL(std::string("raboof"), Command::argument(*_noop, 6));
  CPPUNIT_ASSERT_EQUAL(std::string("rab"),    Command::argument(*_noop, 7));
  CPPUNIT_ASSERT_EQUAL(std::string("oof"),    Command::argument(*_noop, 8));
  CPPUNIT_ASSERT_EQUAL(std::string("oofrab"), Command::argument(*_noop, 9));
}

/*}}}*/
void TestCommand::testSet()/*{{{*/
{
  _noop->set( 0, "foo");
  _noop->set( 1, "bar");
  _noop->set( 2, "foobar");
  _noop->set( 3, "baz");
  _noop->set( 4, "barbaz");
  _noop->set(19, "barfoo");
  _noop->set( 7, "raboof");
  _noop->set( 6, "rab");
  _noop->set( 5, "oof");
  _noop->set( 8, "oofrab");
}

/*}}}*/
void TestCommand::testAmountSet()/*{{{*/
{
  testSet();
  CPPUNIT_ASSERT_EQUAL(
    static_cast<unsigned int>(10), Command::countArguments(*_noop));
}

/*}}}*/
void TestCommand::testOrderSet()/*{{{*/
{
  testSet();
  CPPUNIT_ASSERT_EQUAL(std::string("foo"),    Command::argument(*_noop,  0));
  CPPUNIT_ASSERT_EQUAL(std::string("bar"),    Command::argument(*_noop,  1));
  CPPUNIT_ASSERT_EQUAL(std::string("foobar"), Command::argument(*_noop,  2));
  CPPUNIT_ASSERT_EQUAL(std::string("baz"),    Command::argument(*_noop,  3));
  CPPUNIT_ASSERT_EQUAL(std::string("barbaz"), Command::argument(*_noop,  4));
  CPPUNIT_ASSERT_EQUAL(std::string("barfoo"), Command::argument(*_noop, 19));
  CPPUNIT_ASSERT_EQUAL(std::string("raboof"), Command::argument(*_noop,  7));
  CPPUNIT_ASSERT_EQUAL(std::string("rab"),    Command::argument(*_noop,  6));
  CPPUNIT_ASSERT_EQUAL(std::string("oof"),    Command::argument(*_noop,  5));
  CPPUNIT_ASSERT_EQUAL(std::string("oofrab"), Command::argument(*_noop,  8));
}

/*}}}*/
void TestCommand::testNoOpComplete()/*{{{*/
{
  CPPUNIT_ASSERT_EQUAL(false, _noop->isComplete());
}

/*}}}*/
void TestCommand::testComplete()/*{{{*/
{
  CPPUNIT_ASSERT_EQUAL(false, _ops->isComplete());
  _ops->add("foo");
  CPPUNIT_ASSERT_EQUAL(false, _ops->isComplete());
  _ops->add("bar");
  CPPUNIT_ASSERT_EQUAL(true, _ops->isComplete());
}

/*}}}*/
void TestCommand::testExecute()/*{{{*/
{
  testComplete();
  (*_ops)();
}

/*}}}*/

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
