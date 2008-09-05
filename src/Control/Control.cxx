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
#include <pthread.h>

#include <gloox/jid.h>
#include <gloox/presence.h>
#include <gloox/clientbase.h>
#include <gloox/message.h>
#include <gloox/disco.h>
#include <gloox/error.h>

#include <libsxc/Exception/Exception.hxx>

#include <Control/Control.hxx>
#include <Control/Roster.hxx>
#include <Control/File/Input.hxx>
#include <generateErrorText.hxx>
#include <print.hxx>

#ifdef HAVE_CONFIG_H
#   include <config.hxx>
#endif

#ifdef DEBUG
#   include <sstream>
#endif

/*}}}*/

#include <iostream>

namespace Control
{
    Control::Control(/*{{{*/
        const gloox::JID &jid,
        int port,
        const std::string &name,
        const std::string &version)
    : _client(jid, "", port), // Fill in the passphrase later.
      _roster(_client),
    // FIXME
    //  _output(this, jid.bare()),
      _input(*this, jid.bare()),
      _thread(NULL)
    {
        _client.registerConnectionListener(this);

        // "console" is not exactly what sxc is, but "pc" is described as a
        // full-featured GUI.
        const std::string category = "client";
        const std::string type = "console";
#       if DEBUG
            printLog(
                "Set identity: (category: \"" + category + "\", type: \"" +
                type + "\", name: \"" + name + "\").");
#       endif
        _client.disco()->setIdentity(category, type, name);

#       if DEBUG
            printLog(
                "Set version: (name: \"" + name + "\", version: \"" +
                version + "\").");
#       endif
        _client.disco()->setVersion(name, version);

        _input.listen();
    }/*}}}*/
    Control::~Control()/*{{{*/
    {
#       if DEBUG
            printLog("Exit.");
#       endif
        disconnect();
    }/*}}}*/

    void Control::setPassphrase(const std::string &pass)/*{{{*/
    {
#       if DEBUG
            printLog("Set passphrase: \"" + pass + "\".");
#       endif
        _client.setPassword(pass);
    }/*}}}*/
    void Control::setPresence(/*{{{*/
        gloox::Presence::PresenceType presence,
        int priority,
        const std::string &status)
    {
#       if DEBUG/*{{{*/
            std::string presenceStr;
            switch (presence) {
            case gloox::Presence::Available:
                presenceStr = "Available";
                break;
            case gloox::Presence::Chat:
                presenceStr = "Chat";
                break;
            case gloox::Presence::Away:
                presenceStr = "Away";
                break;
            case gloox::Presence::DND:
                presenceStr = "DND";
                break;
            case gloox::Presence::XA:
                presenceStr = "XA";
                break;
            case gloox::Presence::Unavailable:
                presenceStr = "Unavailable";
                break;
            case gloox::Presence::Probe:
                presenceStr = "Probe";
                break;
            case gloox::Presence::Error:
                presenceStr = "Error";
                break;
            case gloox::Presence::Invalid:
                presenceStr = "Invalid";
                break;
            default:
                presenceStr = "Unknown";
            }
            std::stringstream text;
            text << "Set presence: (\"" << presenceStr << "\" (" << presence << "), priority: " << priority << ", message: \"" << status << "\").";;
            printLog(text.str());
#       endif/*}}}*/

        _client.setPresence(presence, priority, status);

        // Don't connect if already connected or connecting.
        if (_thread)
            return;
        if ("" == _client.password())
            print("Password not set.");
        else
            pthread_create(&_thread, NULL, _run, (void*)this);
    }/*}}}*/
    void Control::setPresence(/*{{{*/
        gloox::Presence::PresenceType presence,
        const std::string &status)
    {
        setPresence(presence, _client.priority(), status);
    }/*}}}*/
    void Control::setPriority(int priority)/*{{{*/
    {
        gloox::Presence &pres = _client.presence();
        setPresence(pres.presence(), priority, pres.status());
    }/*}}}*/
    void Control::disconnect()/*{{{*/
    {
#       if DEBUG
            printLog("Disconnect.");
#       endif
        _client.disconnect();
    }/*}}}*/
    void Control::sendMessage(/*{{{*/
        const gloox::JID &to,
        const std::string &body)
    {
        gloox::Message message(
            gloox::Message::Normal, // Not Chat.
            to,
            body);
        _client.send(message);
    }/*}}}*/
    void Control::handleMessage(/*{{{*/
        const gloox::Message &msg,
        gloox::MessageSession *session)
    {
        // FIXME
        //print(session->target()->full() + ": " + msg.body());
    }/*}}}*/

    void Control::handleError(/*{{{*/
        libsxc::Exception::Exception &e,
        bool isCritical) const
    {
        if (isCritical) {
            printErr(e.getDescription());
            exit(e.getType());
        }
        print(e.getDescription());
    }/*}}}*/

    void Control::print(std::string text) const/*{{{*/
    {
        // FIXME
        //_output->write(text);
    }/*}}}*/

    Roster &Control::getRoster()/*{{{*/
    {
        return _roster;
    }/*}}}*/

    void Control::onConnect()/*{{{*/
    {
#       if DEBUG
            printLog("Connection established.");
#       endif
    }/*}}}*/
    void Control::onDisconnect(gloox::ConnectionError e)/*{{{*/
    {
        std::string text = "Disconnected: " + generateErrorText(
            e,
            _client.streamError(),
            _client.streamErrorText(),
            _client.authError());
        if (!text.empty())
            print(text);
#       if DEBUG
            printLog(text);
#       endif
        //FIXME: Decide whether to reconnect and restart _run or not.
    }/*}}}*/
    bool Control::onTLSConnect(const gloox::CertInfo &info)/*{{{*/
    {
#       if DEBUG
            printLog("Acknowledge TLS certificate.");
#       endif
        return true;
    }/*}}}*/

    void *Control::_run(void *rawThat)/*{{{*/
    {
#       if DEBUG
            printLog("Start socket receiving thread.");
#       endif

        Control *that = (Control *) rawThat;
        that->_client.connect(); // Blocking.

#       if DEBUG
            printLog("End socket receiving thread.");
#       endif

        that->_thread = NULL;

        return (void *) NULL;
    }/*}}}*/
}

// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
