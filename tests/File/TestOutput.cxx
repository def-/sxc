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

#include <string>
#include <fstream>

#include "TestOutput.hxx"

/*}}}*/

const std::string TestOutput::path = "abcoutput.out";

void TestOutput::setUp()/*{{{*/
{
    _output = new OutputDummy(TestOutput::path);
    _output->initialize();
}

/*}}}*/
void TestOutput::tearDown()/*{{{*/
{
    delete _output;
    _output = NULL;

    remove(TestOutput::path.c_str());
}

/*}}}*/
void TestOutput::testOpen()/*{{{*/
{
    _output->open();
}

/*}}}*/
void TestOutput::testClose()/*{{{*/
{
    _output->open();
    _output->close();
}

/*}}}*/
void TestOutput::testWrite()/*{{{*/
{
    std::ifstream input;
    std::string contents;
    const std::string test = "foobar";

    _output->open();
    _output->write(test);
    _output->close();

    input.open(TestOutput::path.c_str());
    getline(input, contents);
    input.close();

    CPPUNIT_ASSERT_EQUAL(std::string("UNITTEST: " + test), contents);
}

/*}}}*/

// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
