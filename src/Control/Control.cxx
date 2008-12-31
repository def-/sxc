#line 1 "sxc:Control/Control.cxx"
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
#include <pthread.h>
#include <sstream>

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

#ifdef HAVE_CONFIG_H
# include <config.hxx>
#endif

#include <libsxc/Logger.hxx>

#ifdef DEBUG
# include <sstream>
#endif

/*}}}*/

using libsxc::Debug;
using libsxc::Error;

namespace Control
{
  Control::Control(/*{{{*/
    const gloox::JID &jid,
    int port,
    const std::string &name,
    const std::string &version)
  : _client(jid, "", port), // Fill in the passphrase later.
    _roster(this, &_client),
#   ifdef DEBUG
      _logHandler(),
#   endif
    _presence(gloox::Presence::Available),
    _priority(0),
    _status(""),
  // FIXME
  //  _output(this, jid.bare()),
    _input(*this),
    _thread()
  {
    _client.registerConnectionListener(this);
    _client.registerMessageHandler(&_roster);

#   ifdef DEBUG
      _client.logInstance().registerLogHandler(
        gloox::LogLevelDebug,
        gloox::LogAreaAll,
        &_logHandler);
#   endif

    // "console" is not exactly what sxc is, but "pc" is described as a
    // full-featured GUI.
    const std::string category = "client";
    const std::string type = "console";

    LOG<Debug>(
      "Set identity: (category: \"" + category + "\", type: \"" +
      type + "\", name: \"" + name + "\").");

    _client.disco()->setIdentity(category, type, name);

    LOG<Debug>(
      "Set version: (name: \"" + name + "\", version: \"" +
      version + "\").");

    _client.disco()->setVersion(name, version);
  }/*}}}*/
  Control::~Control()/*{{{*/
  {
    LOG<Debug>("Exit.");

    disconnect();
    _client.removeConnectionListener(this);
    _client.removeMessageHandler(&_roster);

#   if DEBUG
      _client.logInstance().removeLogHandler(&_logHandler);
#   endif
  }/*}}}*/

  void Control::run()
  {
    _input.listen();
  }
  void Control::setPassphrase(const std::string &pass)/*{{{*/
  {
    LOG<Debug>("Set passphrase: \"" + pass + "\".");

    _client.setPassword(pass);
  }/*}}}*/
  void Control::setPresence(/*{{{*/
    gloox::Presence::PresenceType presence,
    int priority,
    const std::string &status)
  {
    std::stringstream text;
    text << "Set presence: (\"" << libsxc::genPresenceString(presence)
       << "\" (" << presence << "), priority: " << priority
       << ", message: \"" << status << "\").";;
    LOG<Debug>(text.str());

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
    LOG<Debug>("Disconnect.");

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
      LOG<Error>(e.getDescription());
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
  const gloox::JID &Control::getJid()/*{{{*/
  {
    return _client.jid();
  }/*}}}*/

  void Control::onConnect()/*{{{*/
  {
    LOG<Debug>("Connected: Connection established.");
  }/*}}}*/
  void Control::onDisconnect(gloox::ConnectionError e)/*{{{*/
  {
    LOG<Debug>("Disconnected: " + libsxc::genConnErrorString(
      e,
      _client.streamError(),
      _client.streamErrorText(),
      _client.authError(),
      true)); // Debug.

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
    LOG<Debug>("Acknowledge TLS certificate.");

    return true;
  }/*}}}*/

  void *Control::_run(void *rawThat)/*{{{*/
  {
    LOG<Debug>("Start socket receiving thread.");

    Control *that = (Control *) rawThat;
    that->_client.connect(); // Blocking.

    LOG<Debug>("End socket receiving thread.");

    return (void *) NULL;
  }/*}}}*/
}

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
