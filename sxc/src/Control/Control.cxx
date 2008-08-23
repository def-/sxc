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

#include <gloox/jid.h>
#include <gloox/presence.h>
#include <gloox/clientbase.h>
#include <gloox/message.h>

#include <Control/Control.hxx>
#include <Control/Roster.hxx>
#include <generateErrorText.hxx>
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
    Control::Control()/*{{{*/
    : _client(NULL),
      _roster(NULL)
    // FIXME
    //  _input(NULL),
    //  _output(NULL)
    {
    }/*}}}*/

    void Control::initialize(const gloox::JID newJid, int newPort)/*{{{*/
    {
        _jid = newJid;
        _port = newPort;

        // FIXME
        //_output = File::Output(this, jid.bare());
        //_input = File::Input(this, jid.bare());
    }/*}}}*/

    bool Control::setPassword(std::string newPassword)/*{{{*/
    {
        if (_password.empty()) // Empty passwords not allowed in XMPP.
            return false;
        _password = newPassword;
        return true;
    }/*}}}*/

    bool Control::setPresence(/*{{{*/
        gloox::Presence::PresenceType presence,
        int priority,
        const std::string &status)
    {
#       if DEBUG
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
            std::stringstream priorityStr;
            priorityStr << priority;
            printLog(
                "Setting the presence to " + presenceStr + " (Priority: " +
                priorityStr.str() + ", Message: " + status +")");
#       endif

        bool doConnect = false;

        if (!_client) {
            _client = new gloox::Client(_jid, _password, _port);
            _client->registerConnectionListener(this);
            // FIXME: Does this work or do we need an own client class?
            _client->disableRoster();
            _roster = new Roster(_client);
            // Only establish a connection if there is no client object. (first
            // presence change)
            doConnect = true;
        }
        _client->setPresence(presence, priority, status);
        // FIXME: Thread or non-blocking?
        if (doConnect) _client->connect();

        // TODO: Return false
        return true;
    }/*}}}*/

    bool Control::sendMessage(std::string to, std::string body) const/*{{{*/
    {
        if (!_client)
            return false;
        gloox::JID toJid(to); // FIXME: Check for valid jid?
        gloox::Message message(
            gloox::Message::Normal, // or gloox::Chat?
            toJid,
            body);
        _client->send(message);
        return true;
    }/*}}}*/

    void Control::handleMessage(/*{{{*/
        const gloox::Message &msg,
        gloox::MessageSession *session)
    {
        // FIXME
        //print(session->target()->full() + ": " + msg.body());
    }/*}}}*/

    bool addContact(/*{{{*/
        std::string jid,
        std::string message = gloox::EmptyString)
    {
        //if (!_roster)
        //    return false;
        gloox::JID jidJid(jid); // FIXME: Check for valid jid?
        // FIXME: Implement groups?
        gloox::StringList groups;
        // FIXME
        //_roster->add(jidJid, jid, groups);
        return true;
    }/*}}}*/

    bool ackSubscription(std::string jid, bool ack)/*{{{*/
    {
        //if (!_roster)
        //    return false;
        gloox::JID jidJid(jid); // FIXME: Check for valid jid?
        // FIXME
        //_roster->ackSubscriptionRequest(jid, ack);
        return true;
    }/*}}}*/

    bool removeContact(std::string jid)/*{{{*/
    {
        //if (!_roster)
        //    return false;
        gloox::JID jidJid(jid); // FIXME: Check for valid jid?
        //_roster->remove(jidJid);
        // FIXME
        return true;
    }/*}}}*/

    void Control::print(std::string text) const/*{{{*/
    {
        // FIXME
        //_output->write(text);
    }/*}}}*/

    void Control::handleError(/*{{{*/
        Exception::Exception &e,
        bool isCritical) const
    {
        if (isCritical) {
            printErr(e.getDescription());
            exit(e.getType());
        }
        print(e.getDescription());
    }/*}}}*/

    gloox::Client *Control::getClient() const/*{{{*/
    {
        return _client;
    }/*}}}*/

    void Control::onConnect()/*{{{*/
    {
#       if DEBUG
            printLog("Connection established.");
#       endif
    }/*}}}*/

    void Control::onDisconnect(gloox::ConnectionError e)/*{{{*/
    {
        std::string text = generateErrorText(
            e,
            _client->streamError(),
            _client->streamErrorText(),
            _client->authError());
        if (!text.empty())
            print(text);
    }/*}}}*/

    bool Control::onTLSConnect(const gloox::CertInfo &info)/*{{{*/
    {
        return true;
    }/*}}}*/
}

// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
