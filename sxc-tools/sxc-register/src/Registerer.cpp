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

#include <gloox/client.h>
#include <gloox/connectionlistener.h>
#include <gloox/registration.h>

#include <iostream>
#include <string>
#include <cstdio> // stdin
#include <stdexcept> // std::runtime_error

#include <termios.h> // struct termios
#include <stdio.h> // fileno()
#include <string.h> // strerror()
#include <errno.h> // errno

#include "Registerer.h"

/*}}}*/


std::string Registerer::prefix = "sxc-register: ";
std::string Registerer::registrationPrefix = "Registration: ";
std::string Registerer::connectionPrefix = "Connection: ";

void Registerer::start(gloox::JID newJid)/*{{{*/
{
    jid = new gloox::JID(newJid);

    client = new gloox::Client(jid->server());
    client->disableRoster();
    client->registerConnectionListener(this);

    registration = new gloox::Registration(client);
    registration->registerRegistrationHandler(this);

    client->connect(); // Blocking connection.

    delete jid;
    delete registration;
    delete client;
}/*}}}*/

void Registerer::onConnect()/*{{{*/
{
    // Request the registration fields the server requires.
    registration->fetchRegistrationFields();
}/*}}}*/

void Registerer::onDisconnect(gloox::ConnectionError e)/*{{{*/
{
    std::string text;

    switch (e) {
    case gloox::ConnNoError:
        break;
    case gloox::ConnStreamError:
        text = "A stream error occured. The stream has been closed";
        // TODO: Add stream errors.
        break;
    case gloox::ConnStreamVersionError:
        text = "The incoming stream's version is not supported.";
        break;
    case gloox::ConnStreamClosed:
        text = "The stream has been closed by the server.";
        break;
    case gloox::ConnProxyAuthRequired:
        text = "The HTTP/SOCKS5 proxy requires authentication.";
        break;
    case gloox::ConnProxyAuthFailed:
        text = "The HTTP/SOCKS5 proxy authentication failed.";
        break;
    case gloox::ConnProxyNoSupportedAuth:
        text = "The HTTP/SOCKS5 proxy requires an unsupported auth mechanism.";
        break;
    case gloox::ConnIoError:
        text = "An I/O error occured.";
        break;
    case gloox::ConnParseError:
        text = "An XML parse error occured.";
        break;
    case gloox::ConnConnectionRefused:
        text = "The connection was refused by the server (on the socket "
               "level).";
        break;
    case gloox::ConnDnsError:
        text = "Resolving the server's hostname failed.";
        break;
    case gloox::ConnOutOfMemory:
        text = "Out of memory.";
        break;
    case gloox::ConnNoSupportedAuth:
        text = "The auth mechanisms the server offers are not supported or "
               "the server offered no auth mechanisms at all.";
        break;
    case gloox::ConnTlsFailed:
        text = "The server's certificate could not be verified or the TLS "
               "handshake did not complete successfully.";
        break;
    case gloox::ConnTlsNotAvailable:
        text = "The server doesn't offer TLS.";
        break;
    case gloox::ConnCompressionFailed:
        text = "Negotiating or initializing compression failed.";
        break;
    case gloox::ConnUserDisconnected:
        // The user (or higher-level protocol) requested a disconnect.
        break;
    case gloox::ConnNotConnected:
        text = "There is no active connection.";
        break;
    }

    if (!text.empty())
        print(connectionPrefix + text);
}/*}}}*/

void Registerer::handleRegistrationFields(/*{{{*/
    const gloox::JID &from,
    int fields,
    std::string instructions)
{
    struct termios savedTermState;

    gloox::RegistrationFields values;
    values.username = jid->username();

    // Prompt the user for a password./*{{{*/
    try {
        // Save a copy of the console state.
        if (tcgetattr(fileno(stdin), &savedTermState)) // Cin must track stdin.
            throw std::runtime_error(std::string("Get: ") + strerror(errno));

        // Suppress echo so password is not logged.
        struct termios newTermState = savedTermState;
        newTermState.c_lflag &= ~ECHO;

        if (tcsetattr(fileno(stdin), TCSAFLUSH, &newTermState))
            throw std::runtime_error(std::string("Set: ") + strerror(errno));

        // Verify that echo suppression is supported.
        if (newTermState.c_lflag & ECHO)
            throw std::runtime_error(
                std::string("Verify: unable to suppress echo"));

        // Prompt the user for a password.
        std::cout << "Password: " << std::flush;
        getline(std::cin, values.password);
        //std::cin >> values.password;

        // Restore the terminal state.
        tcsetattr(fileno(stdin), TCSANOW, &savedTermState);
        std::cout << std::endl;
    } catch (...) {
        // Restore the terminal state.
        tcsetattr(fileno(stdin), TCSANOW, &savedTermState);

        print("Entering password failed.");
        exit(1);
    }/*}}}*/

    registration->createAccount(fields, values);
}/*}}}*/

void Registerer::handleRegistrationResult(/*{{{*/
    const gloox::JID &from,
    gloox::RegistrationResult result)
{
    std::string text;

    switch (result) {
    case gloox::RegistrationSuccess:
        text = "Succeeded.";
        break;
    case gloox::RegistrationNotAcceptable:
        text = "Not all necassary information provided.";
        break;
    case gloox::RegistrationConflict:
        text = "Username already exists.";
        break;
    case gloox::RegistrationNotAuthorized:
        text = "Not authorized.";
        break;
    case gloox::RegistrationBadRequest:
        text = "Bad request.";
        break;
    case gloox::RegistrationForbidden:
        text = "Forbidden.";
        break;
    case gloox::RegistrationUnexpectedRequest:
        text = "Unexpected request.";
        break;
    default:
        text = "Unknown error.";
        break;
    }

    if (!text.empty())
        print(registrationPrefix + text);

    client->disconnect();
    exit(result); // Exit the program.
}/*}}}*/

void Registerer::print(std::string text)/*{{{*/
{
    std::cout << prefix << text << std::endl;
}/*}}}*/
