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

// INCLUDES/*{{{*/

#include <cstdio>
#include <unistd.h>

#include <string>
#include <fstream>

#include <Exception/FileInputException.hxx>
#include <libsxc/Exception/Type.hxx>
#include "TestInput.hxx"

/*}}}*/

const std::string TestInput::fifoPath = "fifo.in";

void TestInput::setUp()/*{{{*/
{
    _inputDummy = new InputDummy(TestInput::fifoPath);
    _inputDummy->initialize(true);
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
    _inputDummy->create();
}

/*}}}*/
void TestInput::exceptCreateExist()/*{{{*/
{
    // Create a file in the place where create() wants to store the fifo.
    std::ofstream badFile(TestInput::fifoPath.c_str(), std::ios::out);
    // This should fail — or the missplaced file has been overwritten.
    _inputDummy->create();
}

/*}}}*/
void TestInput::testValidate()/*{{{*/
{
    _inputDummy->create();
    _inputDummy->validate();
}

/*}}}*/
void TestInput::exceptValidateMissing()/*{{{*/
{
    // _inputDummy has been initialized with noPhysical=true, which means that
    // initialize() should have not created the physical file. create() has not
    // been called manually. FIFO should be missing, this should fail and throw
    // an exception.
    _inputDummy->validate();
}

/*}}}*/
void TestInput::exceptValidateBad()/*{{{*/
{
    // Create a non-fifo file to let validate() fail with BadFile.
    std::filebuf fake;
    fake.open(TestInput::fifoPath.c_str(), std::ios::out);
    // This should fail and throw an exception.
    _inputDummy->validate();
}

/*}}}*/
void TestInput::testClose()/*{{{*/
{
    _inputDummy->close();
}

/*}}}*/
void TestInput::testListen()/*{{{*/
{
    _inputDummy->create();
    _inputDummy->listen();
    sleep(1);
}

/*}}}*/
void TestInput::testListenClose()/*{{{*/
{
    _inputDummy->create();
    _inputDummy->listen();
    sleep(1);
    _inputDummy->close();
}

/*}}}*/
void TestInput::testWrite()/*{{{*/
{
    _inputDummy->create();
    _inputDummy->listen();

    const std::string testInput = "foobar";
    std::ofstream fifo(TestInput::fifoPath.c_str());
    fifo << testInput << std::flush;
    fifo.close();
    sleep(1);

    CPPUNIT_ASSERT_EQUAL(testInput, _inputDummy->getLastInput());
}

/*}}}*/

// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
