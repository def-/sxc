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

#include <cstdio>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <string>
#include <fstream>

#include <Exit/Code.hxx>
#include "TestInput.hxx"

/*}}}*/

const std::string TestInput::fifoPath = "fifo.in";

void TestInput::setUp()/*{{{*/
{
  _inputDummy = new InputDummy(TestInput::fifoPath);
  _inputDummy->initialize(true);

  // For the case that a previous test did not stop cleanly.
  remove(TestInput::fifoPath.c_str());
}

/*}}}*/
void TestInput::tearDown()/*{{{*/
{
  delete _inputDummy;
  _inputDummy = NULL;

  remove(TestInput::fifoPath.c_str());
}

/*}}}*/
void TestInput::testCreate()/*{{{*/
{
  _inputDummy->_create();
}

/*}}}*/
void TestInput::exceptCreateExist()/*{{{*/
{
  // Create a file in the place where _create() wants to store the fifo.
  std::ofstream badFile(TestInput::fifoPath.c_str(), std::ios::out);
  // This should fail — or the missplaced file has been overwritten.
  _inputDummy->_create();
}

/*}}}*/
void TestInput::testValidate()/*{{{*/
{
  _inputDummy->_create();
  _inputDummy->_validate();
}

/*}}}*/
void TestInput::exceptValidateMissing()/*{{{*/
{
  // _inputDummy has been initialized with noPhysical=true, which means that
  // initialize() should have not created the physical file. _create() has not
  // been called manually. FIFO should be missing, this should fail and throw
  // an exception.
  _inputDummy->_validate();
}

/*}}}*/
void TestInput::exceptValidate200()/*{{{*/
{
  exceptValidateChmod(S_IWUSR);
}

/*}}}*/
void TestInput::exceptValidate400()/*{{{*/
{
  exceptValidateChmod(S_IRUSR);
}

/*}}}*/
void TestInput::exceptValidate604()/*{{{*/
{
  exceptValidateChmod(S_IRUSR | S_IWUSR | S_IROTH);
}

/*}}}*/
void TestInput::exceptValidate640()/*{{{*/
{
  exceptValidateChmod(S_IRUSR | S_IWUSR | S_IRGRP);
}

/*}}}*/
void TestInput::exceptValidateBad()/*{{{*/
{
  // Create a non-fifo file to let _validate() fail with BadFile.
  std::filebuf fake;
  fake.open(TestInput::fifoPath.c_str(), std::ios::out);
  // This should fail and throw an exception.
  _inputDummy->_validate();
}

/*}}}*/
void TestInput::testClose()/*{{{*/
{
  _inputDummy->close();
}

/*}}}*/
void TestInput::testListen()/*{{{*/
{
  _inputDummy->_create();
  _inputDummy->listen();
  sleep(1);
}

/*}}}*/
void TestInput::testListenClose()/*{{{*/
{
  _inputDummy->_create();
  _inputDummy->listen();
  sleep(1);
  _inputDummy->close();
}

/*}}}*/
void TestInput::testReadSimple()/*{{{*/
{
  _inputDummy->_create();
  _inputDummy->listen();

  const std::string testInput = "foobar";
  std::ofstream fifo(TestInput::fifoPath.c_str());
  fifo << testInput << std::flush;
  fifo.close();
  sleep(1);

  CPPUNIT_ASSERT_EQUAL(testInput, _inputDummy->getLastInput());
}

/*}}}*/
void TestInput::testReadNL()/*{{{*/
{
  _inputDummy->_create();
  _inputDummy->listen();

  const std::string testInput = "foobar\nfoobar\n";
  std::ofstream fifo(TestInput::fifoPath.c_str());
  fifo << testInput << std::flush;
  fifo.close();
  sleep(1);

  CPPUNIT_ASSERT_EQUAL(testInput, _inputDummy->getLastInput());
}

/*}}}*/
void TestInput::testReadNull()/*{{{*/
{
  _inputDummy->_create();
  _inputDummy->listen();

  // Create string while avoiding to let it terminate after \0
  std::string testInput = "foo";
  testInput.push_back('\0');
  testInput.append("bar");
  std::ofstream fifo(TestInput::fifoPath.c_str());
  fifo << testInput << std::flush;
  fifo.close();
  sleep(1);

  CPPUNIT_ASSERT_EQUAL(std::string("bar"), _inputDummy->getLastInput());
}

/*}}}*/
void TestInput::testReadTrailNull()/*{{{*/
{
  _inputDummy->_create();
  _inputDummy->listen();

  std::string testInput = "foobar";
  testInput.push_back('\0');
  testInput.push_back('\0');
  std::ofstream fifo(TestInput::fifoPath.c_str());
  fifo << testInput << std::flush;
  fifo.close();
  sleep(1);

  CPPUNIT_ASSERT_EQUAL(std::string("foobar"), _inputDummy->getLastInput());
}

/*}}}*/
void TestInput::testReadLeadNull()/*{{{*/
{
  _inputDummy->_create();
  _inputDummy->listen();

  std::string testInput;
  testInput.push_back ('\0');
  testInput.append("foobar");
  std::ofstream fifo(TestInput::fifoPath.c_str());
  fifo << testInput << std::flush;
  fifo.close();
  sleep(1);

  CPPUNIT_ASSERT_EQUAL(std::string("foobar"), _inputDummy->getLastInput());
}

/*}}}*/
void TestInput::exceptValidateChmod(mode_t mode)/*{{{*/
{
  CPPUNIT_ASSERT_EQUAL(0, mkfifo(TestInput::fifoPath.c_str(), mode));
  // This should fail and throw an exception.
  _inputDummy->_validate();
}

/*}}}*/

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
