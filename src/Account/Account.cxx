#line 2 "sxc:Account/Account.cxx"
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
#include <gloox/connectionbase.h>
#include <gloox/event.h>

#include <libsxc/generateString.hxx>
#include <libsxc/Exception/Exception.hxx>
#include <libsxc/Error/Handler.hxx>

#include <Account/Account.hxx>
#include <Account/Roster.hxx>
#include <Account/File/Input.hxx>
#include <Account/File/Info.hxx>
#include <File/AbcOutput.hxx>

#ifdef HAVE_CONFIG_H
# include <config.hxx>
#endif

#include <libsxc/Debug/Logger.hxx>

#ifdef DEBUG
# include <sstream>
#endif

/*}}}*/

namespace Account
{
  Account::Account(/*{{{*/
    gloox::Client &client,
    Roster &roster,
    ::File::AbcOutput &out,
    File::Info &nfo,
    libsxc::Error::Handler &eh)
  : _thread(0)
  , _client(client) // Fill in the passphrase later.
  , _roster(roster)
#   ifdef DEBUG
  ,   _logHandler()
#   endif
  , _presence(gloox::Presence::Available)
  , _priority(0)
  , _status("")
  , _in(*this, client.jid().bare())
  , _out(out)
  , _nfo(nfo)
  , _eh(eh)
  {
    _client.registerConnectionListener(this);

#   ifdef DEBUG
      _client.logInstance().registerLogHandler(
        gloox::LogLevelDebug,
        gloox::LogAreaAll,
        &_logHandler);
#   endif
  }/*}}}*/
  Account::~Account()/*{{{*/
  {
    LOG("Destructor");

    pthread_t thread = _thread;
    disconnect();
    if (thread) {
      LOG("Joining thread");
      pthread_join(thread, NULL);
    } else {
      LOG("Not joining thread");
    }

    _client.removeConnectionListener(this);

#   if DEBUG
      _client.logInstance().removeLogHandler(&_logHandler);
#   endif
  }/*}}}*/

  void Account::run()/*{{{*/
  {
    _in.listen();
  }/*}}}*/
  void Account::setPassphrase(const std::string &pass)/*{{{*/
  {
    LOG("Set passphrase: \"" + pass + "\".");

    _client.setPassword(pass);
  }/*}}}*/
  void Account::setPresence(/*{{{*/
    gloox::Presence::PresenceType presence,
    int priority,
    const std::string &status)
  {
    std::stringstream text;
    text << "Set presence: (\"" << libsxc::genPresenceString(presence)
       << "\" (" << presence << "), priority: " << priority
       << ", message: \"" << status << "\").";
    LOG(text.str());

    // Don't trust _client, but instead store the presence information
    // locally.
    _presence = presence;
    _priority = priority;
    _status = status;

    _client.setPresence(presence, priority, status);

    if (gloox::StateConnected == _client.state()) {
      _updateInfo();
    }

    // Don't connect if already connected or connecting.
    if (_thread)
      return;
    if ("" == _client.password()) {
      // Empty passwords are invalid in XMPP.
      _eh.print("Password not set.");
    } else {
      pthread_create(&_thread, NULL, _run, (void*)this);
    }
  }/*}}}*/
  void Account::setPresence(/*{{{*/
    gloox::Presence::PresenceType presence,
    const std::string &status)
  {
    setPresence(presence, _priority, status);
  }/*}}}*/
  void Account::setPriority(int priority)/*{{{*/
  {
    setPresence(_presence, priority, _status);
  }/*}}}*/
  void Account::disconnect()/*{{{*/
  {
    LOG("Disconnect.");

    _client.disconnect();
  }/*}}}*/

  void Account::sendMessage(/*{{{*/
    const gloox::JID &to,
    const std::string &body)
  {
    _roster.sendMessage(to, body);
  }/*}}}*/
  void Account::addContact(const gloox::JID &jid)/*{{{*/
  {
    _roster.addContact(jid);
  }/*}}}*/
  void Account::removeContact(const gloox::JID &jid) const/*{{{*/
  {
    _roster.removeContact(jid);
  }/*}}}*/
  void Account::subscribe(const gloox::JID &jid, const std::string &message) const/*{{{*/
  {
    _roster.subscribe(jid, message);
  }/*}}}*/
  void Account::unsubscribe(/*{{{*/
    const gloox::JID &jid,
    const std::string &message) const
  {
    _roster.unsubscribe(jid, message);
  }/*}}}*/
  void Account::acknowledgeSubscription(const gloox::JID &jid) const/*{{{*/
  {
    _roster.acknowledgeSubscription(jid);
  }/*}}}*/
  void Account::declineSubscription(const gloox::JID &jid) const/*{{{*/
  {
    _roster.declineSubscription(jid);
  }/*}}}*/

  void Account::onConnect()/*{{{*/
  {
    _out.write("Connected: Connection established.");

    _updateInfo();
  }/*}}}*/
  void Account::onDisconnect(gloox::ConnectionError e)/*{{{*/
  {
    std::string text = libsxc::genConnErrorString(
      e,
      _client.streamError(),
      _client.streamErrorText(),
      _client.authError(),
      true);
    _out.write("Disconnected: " + text);

    gloox::Presence::PresenceType type = gloox::Presence::Unavailable;
    _nfo.setPresence(type);
    _nfo.setMessage("");

    _roster.reset();
  }/*}}}*/
  bool Account::onTLSConnect(const gloox::CertInfo &info)/*{{{*/
  {
    std::ostringstream ss;
    ss << "TLS certificate received (status: " << info.status
       << ", chain: " << info.chain
       << ", issuer: " << info.issuer
       << ", server: " << info.server
       << ", date_from: " << info.date_from
       << ", date_to: " << info.date_to
       << ", protocol: " << info.protocol
       << ", cipher: " << info.cipher
       << ", mac: " << info.mac
       << ", compression: " << info.compression
       << ")";
    LOG(ss.str());

    LOG("Acknowledge TLS certificate.");

    return true;
  }/*}}}*/

  void *Account::_run(void *rawThat)/*{{{*/
  {
    LOG("Start socket receiving thread.");
    Account *that = (Account *) rawThat;

    if (that->_client.connect(false)) {
      gloox::ConnectionError ce;
      do {
        ce = that->_client.recv();
      } while (gloox::ConnNoError == ce);
    }

    that->_thread = 0; // Reset to be able to restart another thread.
    LOG("End socket receiving thread.");
    return (void *) NULL;
  }/*}}}*/
  void Account::_updateInfo()/*{{{*/
  {
    if (gloox::Presence::Unavailable == _presence) {
      _nfo.setPresence("invisible");
    } else {
      _nfo.setPresence(_presence);
    }
    _nfo.setMessage(_status);
  }/*}}}*/
}

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
