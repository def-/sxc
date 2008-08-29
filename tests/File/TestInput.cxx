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
    try {
        remove(TestInput::fifoPath.c_str());
        _inputDummy = new InputDummy(TestInput::fifoPath);
        _inputDummy->initialize(true);
    } catch (Exception::FileInputException &e) {
        std::cerr << "TestInput::setUp(): FileInputException: "
                  << e.getDescription() << std::endl;
        CPPUNIT_FAIL("Caught FileInputException.");
    } catch (std::exception &e) {
        std::cerr << "TestInput::setUp(): exception: "
                  << e.what() << std::endl;
        CPPUNIT_FAIL("Caught exception.");
    }
}

/*}}}*/
void TestInput::tearDown()/*{{{*/
{
    try {
        delete _inputDummy;
        _inputDummy = NULL;
        remove(TestInput::fifoPath.c_str());
    } catch (std::exception &e) {
        std::cerr << "TestInput::tearDown(): exception: "
                  << e.what() << std::endl;
        CPPUNIT_FAIL("Caught exception.");
    }
}

/*}}}*/
void TestInput::testCreate()/*{{{*/
{
    try {
        std::cout << "checking create... " << std::flush;

        _inputDummy->create();

        std::cout << "ok" << std::endl;
    } catch (Exception::FileInputException &e) {
        std::cout << "fail" << std::endl;
        std::cerr << "TestInput::testCreate(): FileInputException: "
                  << e.getDescription() << std::endl;
        CPPUNIT_FAIL("Caught FileInputException.");
    } catch (std::exception &e) {
        std::cout << "fail" << std::endl;
        std::cerr << "TestInput::testCreate(): exception: "
                  << e.what() << std::endl;
        CPPUNIT_FAIL("Caught exception.");
    }
}

/*}}}*/
void TestInput::failCreateExist()/*{{{*/
{
    try {
        std::cout << "messing with create... " << std::flush;

        // Create a file in the place where create() wants to store the fifo.
        std::ofstream badFile(TestInput::fifoPath.c_str(), std::ios::out);
        // This should fail — or the missplaced file has been overwritten.
        _inputDummy->create();

        std::cout << "fail" << std::endl;
        CPPUNIT_FAIL("Non-FIFO file has been overwritten.");
    } catch (Exception::FileInputException &e) {
        // The above call to create() should have thrown an exception
        CPPUNIT_ASSERT_EQUAL(libsxc::Exception::FileExists, e.getType());
        std::cout << "ok" << std::endl;
    } catch (std::exception &e) {
        std::cout << "fail" << std::endl;
        std::cerr << "TestInput::failCreateExist(): exception: "
                  << e.what() << std::endl;
        CPPUNIT_FAIL("Caught exception.");
    }
}

/*}}}*/
void TestInput::testValidate()/*{{{*/
{
    try {
        std::cout << "checking validate... " << std::flush;

        _inputDummy->create();
        _inputDummy->validate();

        std::cout << "ok" << std::endl;
    } catch (Exception::FileInputException &e) {
        std::cout << "fail" << std::endl;
        std::cerr << "TestInput::testValidate(): FileInputException: "
                  << e.getDescription() << std::endl;
        CPPUNIT_FAIL("Caught FileInputException.");
    } catch (std::exception &e) {
        std::cout << "fail" << std::endl;
        std::cerr << "TestInput::testValidate(): exception: "
                  << e.what() << std::endl;
        CPPUNIT_FAIL("Caught exception.");
    }
}

/*}}}*/
void TestInput::testValidateMissing()/*{{{*/
{
    try {
        std::cout << "messing with validate (missing file)... ";
        std::cout.flush();

        // FIFO should be missing, this should fail and throw an exception.
        _inputDummy->validate();

        std::cout << "fail" << std::endl;
        CPPUNIT_FAIL("False positive!");
    } catch (Exception::FileInputException &e) {
        // The above call to validate() should have been thrown an exception
        // with type FileMissing.
        CPPUNIT_ASSERT_EQUAL(libsxc::Exception::FileMissing, e.getType());
        std::cout << "ok" << std::endl;
    } catch (std::exception &e) {
        std::cout << "fail" << std::endl;
        std::cerr << "TestInput::testValidateMissing(): exception: "
                  << e.what() << std::endl;
        CPPUNIT_FAIL("Caught exception.");
    }
}

/*}}}*/
void TestInput::testValidateBad()/*{{{*/
{
    try {
        std::cout << "messing with validate (bad file)... ";
        std::cout.flush();

        // Create a non-fifo file to let validate() fail with BadFile.
        std::filebuf fake;
        fake.open(TestInput::fifoPath.c_str(), std::ios::out);
        // This should fail and throw an exception.
        _inputDummy->validate();

        std::cout << "fail" << std::endl;
        CPPUNIT_FAIL("False positive!");
    } catch (Exception::FileInputException &e) {
        // The above call to validate() should have been thrown an exception
        // with type BadFile.
        CPPUNIT_ASSERT_EQUAL(libsxc::Exception::BadFile, e.getType());
        std::cout << "ok" << std::endl;
    } catch (std::exception &e) {
        std::cout << "fail" << std::endl;
        std::cerr << "TestInput::testValidateBad(): exception: "
                  << e.what() << std::endl;
        CPPUNIT_FAIL("Caught exception.");
    }
}

/*}}}*/
void TestInput::testClose()/*{{{*/
{
    try {
        std::cout << "checking close... ";
        std::cout.flush();

        _inputDummy->close();

        std::cout << "ok" << std::endl;
    } catch (Exception::FileInputException &e) {
        std::cout << "fail" << std::endl;
        std::cerr << "TestInput::testClose(): FileInputException: "
                  << e.getDescription() << std::endl;
        CPPUNIT_FAIL("Caught FileInputException.");
    } catch (std::exception &e) {
        std::cout << "fail" << std::endl;
        std::cerr << "TestInput::testClose(): exception: "
                  << e.what() << std::endl;
        CPPUNIT_FAIL("Caught exception.");
    }
}

/*}}}*/
void TestInput::testListenClose()/*{{{*/
{
    try {
        std::cout << "checking listen & close... \n  listen... " << std::flush;

        _inputDummy->create();
        _inputDummy->listen();
        sleep(1);

        std::cout << "ok\n  close... " << std::flush;

        _inputDummy->close();

        std::cout << "ok" << std::endl;
    } catch (Exception::FileInputException &e) {
        std::cout << "fail" << std::endl;
        std::cerr << "TestInput::testListenClose(): FileInputException: "
                  << e.getDescription() << std::endl;
        CPPUNIT_FAIL("Caught FileInputException.");
    } catch (std::exception &e) {
        std::cout << "fail" << std::endl;
        std::cerr << "TestInput::testListenClose(): exception: "
                  << e.what() << std::endl;
        CPPUNIT_FAIL("Caught exception.");
    }
}

/*}}}*/
void TestInput::testWrite()/*{{{*/
{
    try {
        std::cout << "checking write... " << std::flush;

        _inputDummy->create();
        _inputDummy->listen();

        const std::string testInput = "foobar";
        std::ofstream fifo(TestInput::fifoPath.c_str());
        fifo << testInput << std::flush;
        fifo.close();
        sleep(1);

        CPPUNIT_ASSERT_EQUAL(testInput, _inputDummy->getLastInput());

        std::cout << "ok" << std::endl;
    } catch (Exception::FileInputException &e) {
        std::cout << "fail" << std::endl;
        std::cerr << "InputDummy::getLastInput(): FileInputException: "
                  << e.getDescription() << std::endl;
        CPPUNIT_FAIL("Caught FileInputException.");
    } catch (std::exception &e) {
        std::cout << "fail" << std::endl;
        std::cerr << "InputDummy::getLastInput(): exception: "
                  << e.what() << std::endl;
        CPPUNIT_FAIL("Caught exception.");
    }
}

/*}}}*/

// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
