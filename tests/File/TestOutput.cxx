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

#include <string>
#include <fstream>

#include "TestOutput.hxx"

/*}}}*/

const std::string TestOutput::path = "abcoutput.out";

void TestOutput::setUp()/*{{{*/
{
    _output = new OutputDummy(TestOutput::path);
}/*}}}*/
void TestOutput::tearDown()/*{{{*/
{
    delete _output;
    _output = NULL;

    remove(TestOutput::path.c_str());
}/*}}}*/
void TestOutput::testInitialize()/*{{{*/
{
    _output->initialize();
}/*}}}*/
void TestOutput::testOpen()/*{{{*/
{
    _output->initialize();
    _output->open();
}/*}}}*/
void TestOutput::testClose()/*{{{*/
{
    _output->initialize();
    _output->open();
    _output->close();
}/*}}}*/
void TestOutput::testWrite()/*{{{*/
{
    std::ifstream input;
    std::string contents;
    const std::string test = "foobar";

    _output->initialize();
    _output->open();
    _output->write(test);
    _output->close();

    input.open(TestOutput::path.c_str());
    getline(input, contents);
    input.close();

    // OutputDummy will prefix everything with "UNITTEST: ".
    CPPUNIT_ASSERT_EQUAL(std::string("UNITTEST: " + test), contents);
}/*}}}*/
void TestOutput::exceptClose()/*{{{*/
{
    _output->initialize();
    _output->close();
}/*}}}*/

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
