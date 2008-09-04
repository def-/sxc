// TODO:
// - more consts and references (speed)
// - comparisons with (const == var)
// - remove compiler warnings (-Wall -Wextra)
// - write some more tests
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

/* $Id$ */

// INCLUDE/*{{{*/

#include <string>

#include <sys/signal.h>
#include <sigc++/adaptors/bind.h>

#include <gloox/jid.h>

#include <libsxc/Option/Parser.hxx>
#include <libsxc/Option/Option.hxx>
#include <libsxc/Option/OptionPort.hxx>
#include <libsxc/Exception/Exception.hxx>

#include <Control/Control.hxx>
#include <SignalHandler.hxx>
#include <print.hxx>

#ifdef HAVE_CONFIG_H
#   include <config.hxx>
#endif

/*}}}*/

#include <gloox/presence.h>
#include <iostream>

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

void dummy()
{
}

/**
 * @author Dennis Felsing
 * @brief The starting point of sxc.
 *
 * Parse the parameters the program was started with and then initialize the
 * @ref Control::Control.
 */
int main(int argc, char *argv[])/*{{{*/
{
    libsxc::Option::Parser parser;
    libsxc::Option::OptionPort port(
        &parser, 'p', "port", "port", "0 - 65535, -1 for default");
    libsxc::Option::Option<std::string> name(
        &parser, ' ', "iqname", "name",
        std::string("Name to announce (default: ") + PACKAGE + ")", PACKAGE);
    libsxc::Option::Option<std::string> version(
        &parser, ' ', "iqversion", "version",
        std::string("Version to announce (default: ") + VERSION + ")", VERSION);
    libsxc::Option::Option<gloox::JID> jid(
        &parser, ' ', "", "jid", "user@domain[/resource]");

    try {
        parser.parse(argv);
    } catch (libsxc::Exception::Exception &e) {
        const std::string &description = e.getDescription();
        if (description == "")
            printErr(
                std::string(PACKAGE) + " " + VERSION + " (C) " + COPYRIGHT);
        else
            printErr(description);

        std::vector<std::string> usage = parser.getUsage();
        for_each(usage.begin(), usage.end(), printErr);

        return e.getType();
    }

    SignalHandler::setHandler(SIGINT, sigc::ptr_fun(&dummy));

    Control::Control control(
        jid.getValue(),
        port.getValue(),
        name.getValue(),
        version.getValue());
    //control.setPassphrase("test");
    //control.setPresence(gloox::Presence::Available);
    //control.getRoster().addContact("folibar@boo");
    pause(); // Wait until a signal is received and its handler returns.

    return 0;
}/*}}}*/

// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
