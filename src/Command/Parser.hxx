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

#ifndef COMMAND_PARSER_HXX
#define COMMAND_PARSER_HXX

// INCLUDE/*{{{*/

#include <Command/Factory.hxx>
#include <Command/Command.hxx>

#include <string>

/*}}}*/

namespace Command
{
  class Parser
  {
    public:
      static std::string substr(
        const std::string& str, std::string::iterator pos);

      Parser(const std::string& input, const Factory& factory);
      virtual ~Parser();
      const std::string& getInput() const;
      Command& parse();
      Command& getCommand() const;

    private:
      std::string _input;
      const Factory* _factory;
      Command* _command;

      void _dispose();
  };
}

#endif // COMMAND_PARSER_HXX

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
