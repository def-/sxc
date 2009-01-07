#line 2 "sxc:tests/Command/NoOp.cxx"
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

#include "NoOp.hxx"

#include <Command/utilities.hxx>
#include <libsxc/Debug/Logger.hxx>

#include <sstream>

/*}}}*/

namespace Mock
{
  void NoOp::_onAdd()/*{{{*/
  {
    LOG("Adding a parameter to a NoOp command.");
  }

  /*}}}*/
  void NoOp::_onSet(/*{{{*/
    unsigned int index,
    const std::string& oldValue)
  {
    std::ostringstream ss;
    ss << "Setting parameter " << index << " of a noop command from '"
       << oldValue << "' to '" << argument(*this, index) << "'.";
    LOG(ss.str());
  }

  /*}}}*/
  void NoOp::_execute() const/*{{{*/
  {
    LOG("Executing noop command.");
  }

  /*}}}*/
}

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
