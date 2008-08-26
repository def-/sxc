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

/* $Id$ */

// INCLUDE/*{{{*/

#include <string>
#include <gloox/jid.h>
#include <cppunit/extensions/HelperMacros.h>

#include <OptionTest.hxx>
#include <libsxc/Exception/OptionException.hxx>
#include <libsxc/Option/Parser.hxx>
#include <libsxc/Option/Option.hxx>
#include <libsxc/Option/OptionPort.hxx>

/*}}}*/

void OptionTest::setUp()/*{{{*/
{
    _parser = new Option::Parser;

    _bool = new Option::Option<bool>(
        _parser, 'a', "bool", "abc", "description");

    _bool2 = new Option::Option<bool>(
        _parser, 'g', "bool2", "abc", "description", true);

    _int = new Option::Option<int>(
        _parser, 'b', "int", "def", "description", 42);

    _float = new Option::Option<float>(
        _parser, 'c', "float", "ghi", "description");

    _char = new Option::Option<char>(
        _parser, 'd', "char", "jkl", "description", 'x');

    _long = new Option::Option<long>(
        _parser, 'e', "long", "foobar", "description");

    _string = new Option::Option<std::string>(
        _parser, 'f', "string", "var", "description", "default");

    _default = new Option::Option<int>(
        _parser, ' ', "", "foo", "description");

    _default2 = new Option::Option<std::string>(
        _parser, ' ', "", "foob", "description");
}/*}}}*/

void OptionTest::tearDown()/*{{{*/
{
    delete _parser;

    delete _bool;
    delete _bool2;
    delete _int;
    delete _float;
    delete _char;
    delete _long;
    delete _string;
    delete _default;
    delete _default2;
}/*}}}*/

void OptionTest::testCorrectParsing()/*{{{*/
{
    const char *argv[] = {
        "sxc-test", "-a", "--float", "1.2345", "--char", "c", "-e",
        "123456789", "123", "bar", NULL};

    try {
        _parser->parse(const_cast<char **>(argv));
    } catch (Exception::OptionException &e) {
        CPPUNIT_FAIL(e.getDescription());
    }

    CPPUNIT_ASSERT(_bool->getValue());
    CPPUNIT_ASSERT(_bool2->getValue());
    CPPUNIT_ASSERT_EQUAL(42, _int->getValue());
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.2345, _float->getValue(), 0.00001);
    CPPUNIT_ASSERT_EQUAL('c', _char->getValue());
    CPPUNIT_ASSERT_EQUAL(123456789L, _long->getValue());
    CPPUNIT_ASSERT_EQUAL(std::string("default"), _string->getValue());
    CPPUNIT_ASSERT_EQUAL(123, _default->getValue());
    CPPUNIT_ASSERT_EQUAL(std::string("bar"), _default2->getValue());
}/*}}}*/

void OptionTest::testMissingObligatoryOption()/*{{{*/
{
    const char *argv[] = {
        "sxc-test", "-a", "--char", "c", "-e", "123456789", "123",
        "bar", NULL};

    try {
        _parser->parse(const_cast<char **>(argv));
    } catch (Exception::OptionException &e) {
        if (Exception::OptionNotSet == e.getType())
            return;
    }
    CPPUNIT_FAIL("Missing obligatory option ignored");
}/*}}}*/

void OptionTest::testValueNotSet()/*{{{*/
{
    const char *argv[] = {
        "sxc-test", "-a", "--char", "c", "-e", "123456789", "123",
        "bar", "--float", NULL};

    try {
        _parser->parse(const_cast<char **>(argv));
    } catch (Exception::OptionException &e) {
        if (Exception::ValueNotSet == e.getType())
            return;
    }
    CPPUNIT_FAIL("Missing value ignored");
}/*}}}*/

void OptionTest::testOptionSetMultipleTimes()/*{{{*/
{
    const char *argv[] = {
        "sxc-test", "-a", "--float", "1.2345", "--char", "d", "--char",
        "c", "-e", "123456789", "123", "bar", NULL};

    try {
        _parser->parse(const_cast<char **>(argv));
    } catch (Exception::OptionException &e) {
        if (Exception::OptionSetMultiple == e.getType())
            return;
    }
    CPPUNIT_FAIL("Option set multiple times");
}/*}}}*/

void OptionTest::testUnknownLongOption()/*{{{*/
{
    const char *argv[] = {
        "sxc-test", "-a", "--float", "1.2345", "--zomfg", "--char", "c",
        "-e", "123456789", "123", "bar", NULL};

    try {
        _parser->parse(const_cast<char **>(argv));
    } catch (Exception::OptionException &e) {
        if (Exception::OptionUnknown == e.getType())
            return;
    }
    CPPUNIT_FAIL("Unknown Option added");
}/*}}}*/

void OptionTest::testUnknownShortOption()/*{{{*/
{
    const char *argv[] = {
        "sxc-test", "-a", "--float", "1.2345", "-z", "--char", "c",
        "-e", "123456789", "123", "bar", NULL};

    try {
        _parser->parse(const_cast<char **>(argv));
    } catch (Exception::OptionException &e) {
        if (Exception::OptionUnknown == e.getType())
            return;
    }
    CPPUNIT_FAIL("Unknown Option added");
}/*}}}*/

void OptionTest::testConflictingShortName()/*{{{*/
{
    try {
        Option::Option<int> conflicting(
            _parser, 'd', "conflicting", "barfoo", "descr");
    } catch (Exception::OptionException &e) {
        if (Exception::OptionsConflicting == e.getType())
            return;
    }
    CPPUNIT_FAIL("Conflicting Option added");
}/*}}}*/

void OptionTest::testConflictingLongName()/*{{{*/
{
    try {
        Option::Option<char> conflicting(
            _parser, 'z', "long", "bar", "descr", 'y');
    } catch (Exception::OptionException &e) {
        if (Exception::OptionsConflicting == e.getType())
            return;
    }
    CPPUNIT_FAIL("Conflicting Option added");
}/*}}}*/

void OptionTest::testJids()/*{{{*/
{
    doTestInvalidJid("foo");
    doTestInvalidJid("123");
    doTestInvalidJid("abc@");
    doTestInvalidJid("@@@");
    doTestInvalidJid("@bcd");

    doTestValidJid("foo@bar");
    doTestValidJid("ra23@192.168.0.1");
    doTestValidJid("wu@127.0.0.1/home");
}/*}}}*/

void OptionTest::testConvertType()/*{{{*/
{
    doTestInvalidConvert<int>("foo");
    doTestInvalidConvert<long>("abc");
    doTestInvalidConvert<char>("ab");
    doTestInvalidConvert<float>("foo");
    doTestInvalidConvert<double>("foo");

    doTestValidConvert<std::string>("foo@bar");
    doTestValidConvert<int>("42");
    doTestValidConvert<long>("42");
    doTestValidConvert<char>("a");
    doTestValidConvert<float>("42.123456");
    doTestValidConvert<double>("42.123456");
}/*}}}*/

void OptionTest::doTestInvalidJid(std::string rawJid)/*{{{*/
{
    Option::Parser parser;
    Option::Option<gloox::JID> jid(
        &parser, 'j', "jid", "barfoo", "descr");

    try {
        jid.setValue(rawJid);
    } catch (Exception::OptionException &e) {
        if (Exception::JidInvalid == e.getType())
            return;
    }
    CPPUNIT_FAIL("Invalid JID " + rawJid + " accepted");
}/*}}}*/

void OptionTest::doTestValidJid(std::string rawJid)/*{{{*/
{
    Option::Parser parser;
    Option::Option<gloox::JID> jid(
        &parser, 'j', "jid", "barfoo", "descr");

    try {
        jid.setValue(rawJid);
    } catch (Exception::OptionException &e) {
        CPPUNIT_FAIL("Valid JID " + rawJid + " not accepted");
    }
}/*}}}*/

template<typename T> void OptionTest::doTestInvalidConvert(std::string rawValue)/*{{{*/
{
    Option::Parser parser;
    Option::Option<T> option(
        &parser, 'a', "abc", "foobar", "descr");

    try {
        option.setValue(rawValue);
    } catch (Exception::OptionException &e) {
        if (Exception::ValueInvalid == e.getType())
            return;
    }
    CPPUNIT_FAIL("Invalid type conversion of " + rawValue + " worked");
}/*}}}*/

template<typename T> void OptionTest::doTestValidConvert(std::string rawValue)/*{{{*/
{
    Option::Parser parser;
    Option::Option<T> option(
        &parser, 'a', "abc", "foobar", "descr");

    try {
        option.setValue(rawValue);
    } catch (Exception::OptionException &e) {
        CPPUNIT_FAIL("Valid type conversion of " + rawValue + " did not work");
    }
}/*}}}*/
// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
