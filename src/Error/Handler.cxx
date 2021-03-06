#line 2 "sxc:Error/Handler.cxx"
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

#ifdef HAVE_CONFIG_H
# include <config.hxx>
#endif

#include <iostream>
#include <sstream>

#include <libsxc/Signal/Waiter.hxx>
#include <libsxc/Signal/stopOn.hxx>
#include <libsxc/Debug/Logger.hxx>
#include <libsxc/Exit/Code.hxx>

#include <Error/Handler.hxx>
#include <File/AbcOutput.hxx>

/*}}}*/

namespace Error
{
  Handler::Handler(libsxc::Signal::Waiter &waiter, File::AbcOutput &out)/*{{{*/
  : libsxc::Signal::Stopper(waiter)
  , _out(out)
  , _exitCode(libsxc::Exit::NoError)
  {
  }/*}}}*/

  int Handler::getExitCode()/*{{{*/
  {
    return _exitCode;
  }/*}}}*/

  void Handler::print(const std::string &message)/*{{{*/
  {
    LOG("Message: \"" + message + "\"");
    _out.write(message);
  }/*}}}*/

  void Handler::printCritical(const std::string &message)/*{{{*/
  {
    std::cerr << message << std::endl;
  }/*}}}*/

  void Handler::terminate(int exitCode)/*{{{*/
  {
    std::ostringstream ss;
    ss << "Exit code: " << exitCode;
    LOG(ss.str());

    _exitCode = exitCode;
    stop(); // Stop the waiter.
  }/*}}}*/
}

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
