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

#ifndef INPUTDUMMY_H
#define INPUTDUMMY_H

// INCLUDES/*{{{*/

#include <string>
#include <File/AbcInput.hxx>

/*}}}*/

/**
 * @class InputDummy
 * @brief Dummy implementation of the ABC File::AbcInput
 *
 * Inherits from the abstract base class File::AbcInput and definines the
 * abstract methods as "dummy" ones that do no "real" work but are optimized for
 * unit tests.
 */
class InputDummy : public File::AbcInput
{
  friend class TestInput;

  public:
    InputDummy(const std::string &filename);
    const std::string &getLastInput() const;

  protected:

  private:
    std::string _filename;
    std::string _lastInput;
    std::string _createPath() const;
    void _handleInput(const std::string&);
};

#endif // INPUTDUMMY_H

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
