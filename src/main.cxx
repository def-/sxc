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


// INCLUDE/*{{{*/

#include <string>
#include <unistd.h>
#include <iostream>

#include <sys/signal.h>
#include <sigc++/adaptors/bind.h>

#include <gloox/jid.h>

#include <libsxc/Option/Parser.hxx>
#include <libsxc/Option/Option.hxx>
#include <libsxc/Option/OptionPort.hxx>
#include <libsxc/Exception/Exception.hxx>
#include <libsxc/Exception/Type.hxx>

#include <Control/Control.hxx>
#include <SignalHandler.hxx>
#include <print.hxx>

#ifdef HAVE_CONFIG_H
#   include <config.hxx>
#endif

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

void dummy()/*{{{*/
{
}/*}}}*/

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

    const unsigned int hostNameSize = 256;
    char hostName[hostNameSize];
    if (0 != gethostname(hostName, hostNameSize)) // This should never happen!
        printErr("Error getting the hostname of this system.");
    const std::string defaultResource = std::string(PACKAGE) + "@" + hostName;
    libsxc::Option::Option<gloox::JID> jid(
        &parser, ' ', "", "jid",
        "user@domain[/resource] (resource default: " + defaultResource + ")");

    try {
        parser.parse(argv);
    } catch (libsxc::Exception::OptionException &e) {
        if (libsxc::Exception::ShowUsage == e.getType()) {
            std::cerr << PACKAGE << " " << VERSION << " (C) " << COPYRIGHT
                      << std::endl;
        } else if (libsxc::Exception::ShowVersion == e.getType()) {
            std::cerr << VERSION << std::endl;
            return libsxc::Exception::NoError;
        } else {
            printErr(e.getDescription());
        }

        std::vector<std::string> usage = parser.getUsage();
        for_each(usage.begin(), usage.end(), printErrRaw);

        if (e.getType() < 0) // No error. (ShowUsage, ShowVersion)
            return libsxc::Exception::NoError;
        return e.getType();
    } catch (libsxc::Exception::Exception &e) {
        printErr(e.getDescription());
        return e.getType();
    }

    gloox::JID jidJid = jid.getValue();
    if ("" == jidJid.resource())
        jidJid.setResource(defaultResource);

    SignalHandler::setHandler(SIGINT, sigc::ptr_fun(&dummy));

    Control::Control *control;
    try {
        control = new Control::Control(
            jidJid,
            port.getValue(),
            name.getValue(),
            version.getValue());
    } catch (libsxc::Exception::Exception &e) {
        printErr(e.getDescription());
        // Don't delete control, as it failed to initialize.
        return e.getType();
    }

    pause(); // Wait until a signal is received and its handler returns.

    delete control;
    return 0;
}/*}}}*/

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
