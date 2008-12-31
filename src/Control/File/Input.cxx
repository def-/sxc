#line 1 "sxc:Control/File/Input.cxx"
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

#ifdef HAVE_CONFIG_H
# include <config.hxx>
#endif

#include <deque>
#include <string>
#include <exception>

#include <Control/Control.hxx>
#include <Control/File/Input.hxx>
#include <Control/Command.hxx>
#include <Exception/InputException.hxx>
#include <libsxc/Exception/Exception.hxx>
#include <libsxc/Logger.hxx>

/*}}}*/

using libsxc::Error;

namespace Control
{
  namespace File
  {
    Input::Input(Control &control)/*{{{*/
    : _control(control)
    {
      initialize();
    }

/*}}}*/
    std::string Input::_createPath() const/*{{{*/
    {
      return _control.getJid().bare() + "/in";
    }

/*}}}*/
    void Input::_handleInput(const std::string &input)/*{{{*/
    {
      try {
        Command command(_control, input);
        command.execute();
      } catch (Exception::InputException &e) {
        // Just an invalid input, nothing serious.
        _control.handleError(e);
      } catch (libsxc::Exception::Exception &e) {
        // This may be something more serious.
        // TODO: Fix handleError() to make use of stderr
        _control.handleError(e);
      } catch (std::exception &e) {
        // This is *really* unexpected.
        LOG<Error>(e.what());
        _control.print(e.what());
      }
    }

/*}}}*/
  }
}

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
