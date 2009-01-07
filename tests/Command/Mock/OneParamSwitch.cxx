#line 2 "sxc:tests/Command/OneParamSwitch.cxx"
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

#include "OneParamSwitch.hxx"

#include <Command/utilities.hxx>

#include <libsxc/Debug/Logger.hxx>
#include <libsxc/Exception/LogicError.hxx>
#include <libsxc/Exception/RuntimeError.hxx>
#include <libsxc/Option/Exception/InvalidValue.hxx>

#include <string>
#include <sstream>

/*}}}*/

namespace Mock
{
  void OneParamSwitch::_onAdd()/*{{{*/
  {
    // Get the number of total arguments, including the one that has just been
    // added.
    const int argc        = countArguments(*this);
    // Get value of the argument that has just been added.
    const std::string arg = argument(*this, argc - 1);

    if (1 == argc) {
      if ("foo" == arg) {
        _expected2ndParam = "bar";
      } else if ("bar" == arg) {
        _expected2ndParam = "foo";
      } else {
        throw libsxc::Option::Exception::InvalidValue(
          "first argument", arg.c_str());
      }
    } else if (2 == argc) {
      if (arg != _expected2ndParam) {
        throw libsxc::Option::Exception::InvalidValue(
          "second argument", arg.c_str());
      }
    } else {
      LOG("Third paramter has been added. This must not happen.");
    }

    std::ostringstream ss;
    ss << "Parameter " << argc << " added with value '" << arg << "'.";
    LOG(ss.str());

    if (argc == 2) {
      // Second argument is okay, command is complete. Call setComplete() to
      // flag this command as complete.
      LOG("Calling setComplete().");
      setComplete();
      LOG("setComplete() sucessfully called.");
    }
  }

  /*}}}*/
  void OneParamSwitch::_onSet(/*{{{*/
    unsigned int index,
    const std::string& oldValue)
  {
    // TODO
    LOG("Thou shalt not call unimplemented methods.");
    throw libsxc::Exception::LogicError(
      "Thou shalt not call unimplemented methods.");
  }

  /*}}}*/
  void OneParamSwitch::_execute() const/*{{{*/
  {
    std::ostringstream ss;
    ss << argument(*this, 0) << " " << argument(*this, 1);
    std::string result(ss.str());
    if ("foo bar" != result && "bar foo" != result) {
      result.insert(0, "Unexpected result: ");
      throw libsxc::Exception::RuntimeError(result.c_str());
    }
  }

  /*}}}*/
}

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
