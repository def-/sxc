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

#include "TestParser.hxx"
#include "Mock/Factory.hxx"
#include "Mock/NoOp.hxx"

#include <Command/Parser.hxx>
#include <Command/Command.hxx>
#include <Command/utilities.hxx>

#include <Command/Exception/CouldNotParse.hxx>
#include <libsxc/Exception/RuntimeError.hxx>
#include <libsxc/Debug/Logger.hxx>

#include <string>
#include <exception>
#include <iostream>
#include <typeinfo>

/*}}}*/

TestParser::TestParser()/*{{{*/
: _parser(NULL)
{
}

/*}}}*/
void TestParser::setUp()/*{{{*/
{
}

/*}}}*/
void TestParser::tearDown()/*{{{*/
{
  if (_parser == NULL)
    return;

  delete _parser;
  _parser = NULL;
}

/*}}}*/
void TestParser::testException()/*{{{*/
{
  libsxc::Exception::RuntimeError cause("Testsuite.");
  LOG("Building CouldNotParse");
  Command::Exception::CouldNotParse e(":test command", cause);
  LOG("Build. Asserting.");
  CPPUNIT_ASSERT_EQUAL(std::string("Testsuite."), std::string(e.getCause()));
  CPPUNIT_ASSERT_EQUAL(
    std::string("Testsuite.\nCould not parse input ':test command'."),
    std::string(e.what()));
}

/*}}}*/
void TestParser::testLifecycle()/*{{{*/
{
  _parser = new Command::Parser("", Mock::factory);
  delete _parser;
  _parser = NULL;
}

/*}}}*/
void TestParser::testGetInput()/*{{{*/
{
  const std::string mock(":mock command to test something.");
  _parser = new Command::Parser(mock, Mock::factory);
  CPPUNIT_ASSERT_EQUAL(mock, _parser->getInput());
}

/*}}}*/
void TestParser::testParseSimple()/*{{{*/
{
  const std::string mock(":noop foo bar foobar");
  _parser = new Command::Parser(mock, Mock::factory);
  _parser->parse();
}

/*}}}*/
void TestParser::testGetCommand()/*{{{*/
{
  const std::string mock(":noop foo bar foobar");
  _parser = new Command::Parser(mock, Mock::factory);
  Command::Command& command1(_parser->parse());
  Command::Command& command2(_parser->getCommand());
}

/*}}}*/
void TestParser::testParseResult()/*{{{*/
{
  const std::string mock(":noop foo bar foobar");
  _parser = new Command::Parser(mock, Mock::factory);
  Command::Command& command(_parser->parse());
  CPPUNIT_ASSERT_EQUAL(std::string("noop"),   Command::argument(command, 0));
  CPPUNIT_ASSERT_EQUAL(std::string("foo"),    Command::argument(command, 1));
  CPPUNIT_ASSERT_EQUAL(std::string("bar"),    Command::argument(command, 2));
  CPPUNIT_ASSERT_EQUAL(std::string("foobar"), Command::argument(command, 3));
  CPPUNIT_ASSERT_EQUAL(
    static_cast<unsigned int>(4), Command::countArguments(command));
}

/*}}}*/
void TestParser::testParseComplex()/*{{{*/
{
  const std::string mock(":noop 'foo bar' foobar");
  _parser = new Command::Parser(mock, Mock::factory);
  Command::Command& command(_parser->parse());
  CPPUNIT_ASSERT_EQUAL(std::string("noop"),   Command::argument(command, 0));
  CPPUNIT_ASSERT_EQUAL(std::string("foo bar"),Command::argument(command, 1));
  CPPUNIT_ASSERT_EQUAL(std::string("foobar"), Command::argument(command, 3));
  CPPUNIT_ASSERT_EQUAL(
    static_cast<unsigned int>(3), Command::countArguments(command));
}

/*}}}*/

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
