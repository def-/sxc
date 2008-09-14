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

#include <libsxc/generateString.hxx>
#include <libsxc/Exception/Exception.hxx>

#include <Control/Control.hxx>
#include <Control/Roster.hxx>
#include <Control/File/Input.hxx>
#include <print.hxx>

#ifdef HAVE_CONFIG_H
#   include <config.hxx>
#endif

#ifdef DEBUG
#   include <sstream>
#endif

/*}}}*/


namespace Control
{
    Control::Control(/*{{{*/
        const gloox::JID &jid,
        int port,
        const std::string &name,
        const std::string &version)
    : _client(jid, "", port), // Fill in the passphrase later.
      _roster(this, &_client),
#     ifdef DEBUG
          _logHandler(),
#     endif
      _presence(gloox::Presence::Available),
      _priority(0),
      _status(""),
    // FIXME
    //  _output(this, jid.bare()),
      _input(*this, jid.bare()),
      _thread()
    {
        _client.registerConnectionListener(this);
        _client.registerMessageHandler(&_roster);

#       ifdef DEBUG
            _client.logInstance().registerLogHandler(
                gloox::LogLevelDebug,
                gloox::LogAreaAll,
                &_logHandler);
#       endif

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
        _client.removeConnectionListener(this);
        _client.removeMessageHandler(&_roster);

#       if DEBUG
            _client.logInstance().removeLogHandler(&_logHandler);
#       endif
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
            std::stringstream text;
            text << "Set presence: (\"" << libsxc::genPresenceString(presence)
                 << "\" (" << presence << "), priority: " << priority
                 << ", message: \"" << status << "\").";;
            printLog(text.str());
#       endif/*}}}*/

        // Don't trust _client, but instead store the presence information
        // locally.
        _presence = presence;
        _priority = priority;
        _status = status;

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
        setPresence(presence, _priority, status);
    }/*}}}*/
    void Control::setPriority(int priority)/*{{{*/
    {
        setPresence(_presence, priority, _status);
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
            printLog("Connected: Connection established.");
#       endif
    }/*}}}*/
    void Control::onDisconnect(gloox::ConnectionError e)/*{{{*/
    {
#       if DEBUG
            printLog("Disconnected: " + libsxc::genConnErrorString(
                e,
                _client.streamError(),
                _client.streamErrorText(),
                _client.authError(),
                true)); // Debug.
#       endif

        std::string text = libsxc::genConnErrorString(
            e,
            _client.streamError(),
            _client.streamErrorText(),
            _client.authError());
        if (!text.empty())
            print("Disconnected: " + text);
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

        return (void *) NULL;
    }/*}}}*/
}

// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
