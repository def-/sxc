#line 1 "sxc:main.cxx"
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

#include <string>
#include <iostream>
#include <signal.h>

#include <gloox/jid.h>

#include <libsxc/Option/Parser.hxx>
#include <libsxc/Option/parse.hxx>
#include <libsxc/Option/Option.hxx>
#include <libsxc/Option/OptionPort.hxx>
#include <libsxc/Exception/Exception.hxx>
#include <libsxc/Exception/Type.hxx>
#include <libsxc/getHostName.hxx>

#include <libsxc/Signal/Waiter.hxx>
#include <libsxc/Signal/stopOn.hxx>

#include <Control/Control.hxx>
#include <Error/Handler.hxx>

#ifdef HAVE_CONFIG_H
# include <config.hxx>
#endif

#include <libsxc/Logger.hxx>

/*}}}*/

/**
 * @mainpage sxc Documentation
 *
 * @section contents Contents
 * @ref desc_sec
 *
 * @section desc_sec Description
 * sxc (pronounced "sexy) is for jabber what ii (irc it / irc improved) is for
 * IRC: A minimalistic file-based jabber client which runs in the background
 * and can be controlled with basic command line tools to read from / write
 * into the files/FIFOs sxc creates.
 */

#include <libsxc/Debug/Logger.hxx>

/**
 * @brief The starting point of sxc.
 *
 * Parse the parameters the program was started with and then initialize the
 * @ref Control::Control.
 */
int main(int argc, char *argv[])/*{{{*/
{
  LOG2("foobar");
  libsxc::Option::Parser parser;
  parser.setHelp(PACKAGE " " VERSION " (C) " COPYRIGHT);
  parser.setVersion(VERSION);
  libsxc::Option::Option<bool> defHelp(
    &parser, 'h', "help", "Show help and exit");
  libsxc::Option::Option<bool> defVersion(
    &parser, 'V', "version", "Show version and exit");
  libsxc::Option::OptionPort port(
    &parser, 'p', "port", "port", "0 - 65535, -1 for default");
  libsxc::Option::Option<std::string> name(
    &parser, ' ', "iqname", "name",
    std::string("Name to announce (default: ") + PACKAGE + ")", PACKAGE);
  libsxc::Option::Option<std::string> version(
    &parser, ' ', "iqversion", "version",
    std::string("Version to announce (default: ") + VERSION + ")", VERSION);

  const std::string defaultResource =
    std::string(PACKAGE) + "@" + libsxc::getHostName();
  libsxc::Option::Option<gloox::JID> jid(
    &parser, ' ', "", "jid",
    "user@domain[/resource] (resource default: " + defaultResource + ")");

  libsxc::Option::parse(parser, argv);
  // FIXME: Handle exceptions.

  gloox::JID jidJid = jid.getValue();
  if ("" == jidJid.resource())
    jidJid.setResource(defaultResource);

  Control::Control *control;
  try {
    control = new Control::Control(
      jidJid,
      port.getValue(),
      name.getValue(),
      version.getValue());
  } catch (libsxc::Exception::Exception &e) {
    LOG<libsxc::Error>(e.getDescription());
    // Don't delete control, as it failed to initialize.
    return e.getType();
  }

  // Has to be created before running any thread.
  libsxc::Signal::Waiter waiter;
  Error::Handler handler(waiter);

  waiter.reg(SIGINT, handler);
  waiter.reg(SIGTERM, handler);
  //libsxc::Signal::stopOn(waiter, SIGINT);
  //libsxc::Signal::stopOn(waiter, SIGTERM);

  control->run(); // Starts threads.

  waiter.run(); // Blocking. From this moment on signals are handled.

  delete control;
  return handler.getExitCode();
}/*}}}*/

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
