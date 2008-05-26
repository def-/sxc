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

#include <iostream>
#include <gloox/jid.h>
#include <gloox/presence.h>
#include <gloox/clientbase.h>

#include "Control.h"
#include "Roster.h"

/*}}}*/


namespace Control
{
    const std::string Control::_outputPrefix = "sxc: ";
    const std::string Control::_connectionPrefix = "sxc: ";


    void Control::initialize(const gloox::JID newJid, int newPort)/*{{{*/
    {
        _jid = newJid;
        _port = newPort;

        //_output = File::Output(jid.bare());
        //_input = File::Input(jid.bare());
    }/*}}}*/

    bool Control::setPresence(/*{{{*/
        gloox::Presence::PresenceType presence,
        int priority,
        const std::string &status)
    {
        bool doConnect = false;

        if (!_client) {
            _client = new gloox::Client(_jid, _password, _port);
            _client->registerConnectionListener(this);
            _roster = new Roster(_client);
            doConnect = true;
        }
        _client->setPresence(presence, priority, status);
        if (doConnect) _client->connect();
    }/*}}}*/

    void Control::print(std::string text)/*{{{*/
    {
        //_output.write(text);
    }/*}}}*/

    void Control::printStdErr(std::string text)/*{{{*/
    {
        std::cerr << _outputPrefix << text << std::endl;
    }/*}}}*/

    void Control::onConnect()/*{{{*/
    {
        // TODO: print or printStdErr?
        #if DEBUG
            print("Connection established.");
        #endif
    }/*}}}*/

    void Control::onDisconnect(gloox::ConnectionError e)/*{{{*/
    {
        // TODO: more functionality (DEBUG, authError, streamErrorText,
        //       streamError)

        std::string text;

        switch (e) {
        case gloox::ConnNoError:
            break;
        case gloox::ConnStreamError:
            text = "A stream error occured. The stream has been closed";
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
            text = "The HTTP/SOCKS5 proxy requires an unsupported auth "
                   "mechanism.";
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
            text = "The auth mechanisms the server offers are not supported "
                   "or the server offered no auth mechanisms at all.";
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
            print(_connectionPrefix + text);
    }/*}}}*/

    gloox::ClientBase *Control::getClient()/*{{{*/
    {
        return _client;
    }/*}}}*/
}
// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
