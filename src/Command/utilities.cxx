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

// INCLUDE/*{{{*/

#include <Command/utilities.hxx>

#include <Command/Command.hxx>
#include <libsxc/Exception/RuntimeError.hxx>

#include <sstream>
#include <string>
#include <map>

/*}}}*/

namespace Command
{
  unsigned int countArguments(const Command& command)/*{{{*/
  {
    size_t argc = command.container().size();
    return static_cast<unsigned int>(argc);
  }

/*}}}*/
  std::string argument(const Command& command, unsigned int index)/*{{{*/
  {
    const std::map<unsigned int, std::string>::const_iterator
      arg = command.container().find(index);
    if (arg == command.container().end()) {
      std::ostringstream message;
      message << "Command does not contain an argument with index '"
              << index << "'.";
      // TODO: Throw OutOfBounds here.
      throw libsxc::Exception::RuntimeError(message.str().c_str());
    }
    return arg->second;
  }

/*}}}*/
}
// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
