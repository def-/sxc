#line 2 "sxc:main.cxx"
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

#include <string>
#include <iostream>
#include <signal.h>

#include <gloox/jid.h>

#include <libsxc/Debug/Logger.hxx>
#include <libsxc/Option/Parser.hxx>
#include <libsxc/Option/Option.hxx>
#include <libsxc/Option/OptionPort.hxx>
#include <libsxc/Exception/Exception.hxx>
#include <libsxc/Exit/Code.hxx>
#include <libsxc/Signal/Waiter.hxx>
#include <libsxc/Signal/stopOn.hxx>
#include <libsxc/getHostName.hxx>

#include <Account/Account.hxx>
#include <Account/Roster.hxx>
#include <Account/File/Output.hxx>
#include <Error/Handler.hxx>
#include <setupClient.hxx>
#include <File/createDir.hxx>

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
 * @ref Account::Account.
 */
int main(int argc, char *argv[])/*{{{*/
{
  libsxc::Option::Parser parser;
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
  libsxc::Option::Option<gloox::JID> jidRaw(
    &parser, ' ', "", "jid",
    "user@domain[/resource] (resource default: " + defaultResource + ")");

  try {
    parser.parse(argv);
  } catch (libsxc::Exception::Exception &e) {
    std::cerr << e.what() << std::endl;
    return e.getExitCode();
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
    return libsxc::Exit::General;
  } catch (...) {
    std::cerr << "Unexpected error parsing options." << std::endl;
    return libsxc::Exit::General;
  }

  if (parser.doShowHelp()) {
    std::cerr << PACKAGE " " VERSION " (C) " COPYRIGHT << std::endl;

    std::vector<std::string> usage = parser.getUsage();
    for(
    std::vector<std::string>::iterator it = usage.begin();
    usage.end() != it;
    ++it) {
      std::cerr << *it << std::endl;
    }
    return libsxc::Exit::NoError;
  }

  if (parser.doShowVersion()) {
    std::cerr << VERSION << std::endl;
    return libsxc::Exit::NoError;
  }

  gloox::JID jid = jidRaw.getValue();
  if ("" == jid.resource())
    jid.setResource(defaultResource);

  // Fill in the passphrase later.
  gloox::Client client(jid, "", port.getValue());
  setupClient(client, name.getValue(), version.getValue());

  File::createDir(jid.bare());

  Account::File::Output out(jid.bare());

  Account::Roster roster(client, out);

  Account::Account *account;
  try {
    account = new Account::Account(client, roster, out);
  } catch (libsxc::Exception::Exception &e) {
    LOG<libsxc::Error>(e.what());
    // Don't delete account, as it failed to initialize.
    return e.getExitCode();
  }

  // Has to be created before running any thread.
  libsxc::Signal::Waiter waiter;
  Error::Handler handler(waiter);

  waiter.reg(SIGINT, handler);
  waiter.reg(SIGTERM, handler);

  account->run(); // Starts threads.

  waiter.run(); // Blocking. From this moment on signals are handled.

  delete account;
  return handler.getExitCode();
}/*}}}*/

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
