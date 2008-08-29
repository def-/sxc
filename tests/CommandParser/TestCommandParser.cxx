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

// #include <cstdio>
// #include <unistd.h>

#include <algorithm>
#include <iostream>
#include <string>
#include <deque>
#include <list>

#include <cppunit/Exception.h>
#include <Exception/InputException.hxx>
#include <libsxc/Exception/Type.hxx>
#include "TestCommandParser.hxx"
#include "CommandParserDummy.hxx"

/*}}}*/

TestCommandParser::TestCommandParser()/*{{{*/
: _parser(NULL)
{
    /*
    it = map.insert(it, command("one", param(1, false)));
    it = map.insert(it, command("1++", param(1, true)));
    it = map.insert(it, command("two", param(2, false)));
    it = map.insert(it, command("2++", param(2, true)));
    it = map.insert(it, command("thr", param(3, false)));
    it = map.insert(it, command("3++", param(3, true)));
    it = map.insert(it, command("fou", param(4, false)));
    it = map.insert(it, command("4++", param(4, true)));
    */
    // Add some valid commands.
    // The value of the parameters is written behind them.
    _goodCommands.push_back(":one foo bar"); // "foo bar"
    _goodCommands.push_back(":1++ foo bar"); // foo, bar
    _goodCommands.push_back(":two foo bar"); // foo, bar
    _goodCommands.push_back(":2++ foo bar"); // foo, bar
    _goodCommands.push_back(":thr foo bar rab oof"); // foo, bar, "rab oof"
    _goodCommands.push_back(":3++ foo bar rab oof"); // foo, bar, rab, oof
    _goodCommands.push_back(":fou foo bar rab oof"); // foo, bar, rab, oof
    // foo, bar, rab, oof, "foobar raboof":
    _goodCommands.push_back(":4++ foo bar rab oof foobar raboof");

    _noCommands.push_back("This is not a command.");
    _noCommands.push_back("!This neither!.");
    _noCommands.push_back(" :add user@example.org Too bad, leading whitespace not ignored");
    _noCommands.push_back("/foo no command");
}

/*}}}*/
void TestCommandParser::setUp()/*{{{*/
{
}

/*}}}*/
void TestCommandParser::tearDown()/*{{{*/
{
    if (NULL != _parser) {
        delete _parser;
        _parser = NULL;
    }
}

/*}}}*/
void TestCommandParser::testLifecycle()/*{{{*/
{
    try {
        std::cout << "checking constructor... " << std::flush;

        _parser = new CommandParserDummy("[empty]");

        std::cout << "ok\nchecking destructor... " << std::flush;

        delete _parser;
        _parser = NULL;

        std::cout << "ok" << std::endl;
    } catch (Exception::InputException &e) {
        std::cout << "fail" << std::endl;
        std::cerr << "TestCommandParser::testLifecycle(): "
                  << "InputException: " << e.getDescription() << std::endl;
        CPPUNIT_FAIL("Caught InputException.");
    } catch (std::exception &e) {
        std::cout << "fail" << std::endl;
        std::cerr << "TestCommandParser::testLifecycle(): exception: "
                  << e.what() << std::endl;
        CPPUNIT_FAIL("Caught exception.");
    }
}

/*}}}*/
void TestCommandParser::testParse()/*{{{*/
{
    try {
        std::cout << "checking parser... " << std::flush;

        std::list<std::string>::iterator it =  _goodCommands.begin();
        for ( ; it != _goodCommands.end(); ++it) {
            _parser = new CommandParserDummy(*it);
            _parser->parse();
            delete _parser;
            _parser = NULL;
        }

        std::cout << "ok" << std::endl;
    } catch (Exception::InputException &e) {
        std::cout << "fail" << std::endl;
        std::cerr << "TestCommandParser::testParse(): "
                  << "InputException: " << e.getDescription() << std::endl;
        CPPUNIT_FAIL("Caught InputException.");
    } catch (std::exception &e) {
        std::cout << "fail" << std::endl;
        std::cerr << "TestCommandParser::testParse(): exception: "
                  << e.what() << std::endl;
        CPPUNIT_FAIL("Caught exception.");
    }
}

/*}}}*/
void TestCommandParser::testGetName()/*{{{*/
{
    try {
        std::cout << "checking returning of name... " << std::flush;

        std::list<std::string>::iterator it =  _goodCommands.begin();
        for ( ; it != _goodCommands.end(); ++it) {
            _parser = new CommandParserDummy(*it);
            _parser->parse();
            const std::string name = _parser->getName();

            if ("one" != name && "1++" != name && "two" != name && "2++" != name
            && "thr" != name && "3++" != name && "fou" != name && "4++" != name)
                CPPUNIT_FAIL("Invalid command. \
                             Bug in AbcCommandParser or UnitTest outdated.");

            delete _parser;
            _parser = NULL;
        }

        std::cout << "ok" << std::endl;
    } catch (Exception::InputException &e) {
        std::cout << "epic fail" << std::endl;
        CPPUNIT_FAIL(e.getDescription());
    } catch (CppUnit::Exception &e) {
        std::cout << "fail" << std::endl;
        std::cerr << "Dumping bad command.\n";
        std::cerr << "command    = \"" << _parser->get()                << "\"\n";
        std::cerr << "name       = \"" << _parser->getName()            << "\"\n";
        std::cerr.flush();
        throw e;
    } catch (std::exception &e) {
        std::cout << "epic fail" << std::endl;
        throw e;
    }
}

/*}}}*/
void TestCommandParser::testGetParameterString()/*{{{*/
{
    try {
        std::cout << "checking parameters... " << std::flush;

        std::list<std::string>::iterator it =  _goodCommands.begin();
        for ( ; it != _goodCommands.end(); ++it) {
            _parser = new CommandParserDummy(*it);
            _parser->parse();
            const std::string name       = _parser->getName();
            const std::string parameters = _parser->getParameterString();
            if (name == "one" || name == "1++" || name == "two" || name == "2++") {
                CPPUNIT_ASSERT_EQUAL(std::string("foo bar"), parameters);
            } else if (name == "thr" || name == "3++" || name == "fou") {
                CPPUNIT_ASSERT_EQUAL(std::string("foo bar rab oof"), parameters);
            } else if (name == "4++") {
                CPPUNIT_ASSERT_EQUAL(std::string("foo bar rab oof foobar raboof"),
                                     parameters);
            } else {
                CPPUNIT_FAIL("Invalid command. Bug in AbcCommandParser or UnitTest outdated.");
            }

            delete _parser;
            _parser = NULL;
        }

        std::cout << "ok" << std::endl;
    } catch (Exception::InputException &e) {
        std::cout << "epic fail" << std::endl;
        CPPUNIT_FAIL(e.getDescription());
    } catch (CppUnit::Exception &e) {
        std::cout << "fail" << std::endl;
        std::cerr << "Dumping bad command.\n";
        std::cerr << "command    = \"" << _parser->get()                << "\"\n";
        std::cerr << "name       = \"" << _parser->getName()            << "\"\n";
        std::cerr.flush();
        throw e;
    } catch (std::exception &e) {
        std::cout << "epic fail" << std::endl;
        throw e;
    }
}

/*}}}*/
void TestCommandParser::testGetParsed()/*{{{*/
{
    try {
        std::cout << "checking parsed results... " << std::flush;

        std::list<std::string>::iterator it =  _goodCommands.begin();
        for ( ; it != _goodCommands.end(); ++it) {
            _parser = new CommandParserDummy(*it);
            _parser->parse();
            std::deque<std::string> parsed = _parser->getParsed();
            const std::string name = parsed.at(0);
            // Amount of parameters:
            const int cArgs= (int) parsed.size() - 1;
            if (name == "one") {
                CPPUNIT_ASSERT_EQUAL(1, cArgs);
                CPPUNIT_ASSERT_EQUAL(std::string("foo bar"), parsed.at(1));
            } else if (name == "1++" || name == "two" || name == "2++") {
                CPPUNIT_ASSERT_EQUAL(2, cArgs);
                CPPUNIT_ASSERT_EQUAL(std::string("foo"), parsed.at(1));
                CPPUNIT_ASSERT_EQUAL(std::string("bar"), parsed.at(2));
            } else if (name == "thr") {
                CPPUNIT_ASSERT_EQUAL(3, cArgs);
                CPPUNIT_ASSERT_EQUAL(std::string("foo"), parsed.at(1));
                CPPUNIT_ASSERT_EQUAL(std::string("bar"), parsed.at(2));
                CPPUNIT_ASSERT_EQUAL(std::string("rab oof"), parsed.at(3));
            } else if (name == "3++" || name == "fou") {
                CPPUNIT_ASSERT_EQUAL(4, cArgs);
                CPPUNIT_ASSERT_EQUAL(std::string("foo"), parsed.at(1));
                CPPUNIT_ASSERT_EQUAL(std::string("bar"), parsed.at(2));
                CPPUNIT_ASSERT_EQUAL(std::string("rab"), parsed.at(3));
                CPPUNIT_ASSERT_EQUAL(std::string("oof"), parsed.at(4));
            } else if (name == "4++") {
                CPPUNIT_ASSERT_EQUAL(5, cArgs);
                CPPUNIT_ASSERT_EQUAL(std::string("foo"), parsed.at(1));
                CPPUNIT_ASSERT_EQUAL(std::string("bar"), parsed.at(2));
                CPPUNIT_ASSERT_EQUAL(std::string("rab"), parsed.at(3));
                CPPUNIT_ASSERT_EQUAL(std::string("oof"), parsed.at(4));
                CPPUNIT_ASSERT_EQUAL(std::string("foobar raboof"), parsed.at(5));
            } else {
                CPPUNIT_FAIL("Invalid command. \
                             Bug in AbcCommandParser or UnitTest outdated.");
            }
            delete _parser;
            _parser = NULL;
        }

        std::cout << "ok" << std::endl;
    } catch (Exception::InputException &e) {
        std::cout << "epic fail" << std::endl;
        CPPUNIT_FAIL(e.getDescription());
    } catch (CppUnit::Exception &e) {
        std::cout << "fail" << std::endl;
        std::cerr << "Dumping bad command.\n";
        std::cerr << "command    = \"" << _parser->get()                << "\"\n";
        std::cerr << "name       = \"" << _parser->getName()            << "\"\n";
        std::cerr << "parameters = \"" << _parser->getParameterString() << "\"\n";
        std::deque<std::string> parsed = _parser->getParsed();
        std::deque<std::string>::iterator it = parsed.begin();
        for ( ; it != parsed.end(); ++it) {
            std::cerr << "*it = " << *it << "\n";
        }
        std::cerr.flush();
        throw e;
    } catch (std::exception &e) {
        std::cout << "epic fail" << std::endl;
        throw e;
    }
}

/*}}}*/
void TestCommandParser::failParseNoCommand()/*{{{*/
{
    std::cout << "messing with command parsing (not a command)... ";
    std::cout.flush();

    std::list<std::string>::iterator it = _noCommands.begin();
    for ( ; it != _noCommands.end(); ++it) {
        try {
            _parser = new CommandParserDummy(*it);
            _parser->parse();

            std::cout << "fail" << std::endl;
            CPPUNIT_FAIL("False positive.");
        } catch (Exception::InputException &e) {
            CPPUNIT_ASSERT_EQUAL(libsxc::Exception::NoCommand, e.getType());
        } catch (CppUnit::Exception &e) {
            std::cout << "fail" << std::endl;
            throw e;
        } catch (std::exception &e) {
            std::cout << "fail" << std::endl;
            throw e;
        }
        delete _parser;
        _parser = NULL;
    }
    std::cout << "ok" << std::endl;
}

/*}}}*/
void TestCommandParser::failParseInvCommand()/*{{{*/
{
    std::list<std::string>::iterator it = _invalidCommands.begin();
    for ( ; it != _invalidCommands.end(); ++it) {
        try {
            _parser = new CommandParserDummy(*it);
            _parser->parse();

            std::cout << "fail" << std::endl;
            CPPUNIT_FAIL("False positive.");
        } catch (Exception::InputException &e) {
            CPPUNIT_ASSERT_EQUAL(libsxc::Exception::NoCommand, e.getType());
        } catch (CppUnit::Exception &e) {
            std::cout << "fail" << std::endl;
            throw e;
        } catch (std::exception &e) {
            std::cout << "fail" << std::endl;
            throw e;
        }
        delete _parser;
        _parser = NULL;
    }
}

/*}}}*/
void TestCommandParser::failParseInvParam() /*{{{*/
{
    std::list<std::string>::iterator it = _invalidParamCommands.begin();
    for ( ; it != _invalidParamCommands.end(); ++it) {
        try {
            _parser = new CommandParserDummy(*it);
            _parser->parse();

            std::cout << "fail" << std::endl;
            CPPUNIT_FAIL("False positive.");
        } catch (Exception::InputException &e) {
            CPPUNIT_ASSERT_EQUAL(libsxc::Exception::NoCommand, e.getType());
        } catch (CppUnit::Exception &e) {
            std::cout << "fail" << std::endl;
            throw e;
        } catch (std::exception &e) {
            std::cout << "fail" << std::endl;
            throw e;
        }
        delete _parser;
        _parser = NULL;
    }
}

/*}}}*/

// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
