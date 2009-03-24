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

#ifndef KEEPALIVE_HXX
#define KEEPALIVE_HXX

// INCLUDES/*{{{*/

#include <string>

#include <pthread.h>

#include <gloox/client.h>
#include <gloox/connectionlistener.h>
#include <gloox/eventhandler.h>

/*}}}*/

class KeepAlive : public gloox::EventHandler, gloox::ConnectionListener
{
  public:
    //KeepAlive(gloox::Client &, interval = 120, timeout = 120)/*{{{*/

    /**
     * @param interval The time between the pings.
     * @param timeout The time to wait for a pong.
     */
    KeepAlive(
      gloox::Client &client,
      unsigned int interval = 120,
      unsigned int timeout = 120);

/*}}}*/
    //~KeepAlive();/*{{{*/

    /**
     */
    ~KeepAlive();

/*}}}*/

    //void run();/*{{{*/

    /**
     * Has to be called in order to use the KeepAlive object.
     */
    void run();

/*}}}*/
    //void handleEvent(const gloox::Event &event);/*{{{*/

    /**
     * Handles incomming ping and pong events.
     */
    void handleEvent(const gloox::Event &event);

/*}}}*/
    void onConnect() {}
    bool onTLSConnect(const gloox::CertInfo &info) {return true;}
    //void onDisconnect(gloox::ConnectionError e);/*{{{*/

    /**
     * Stop waiting if a disconnect is received, so we don't disconnect again.
     */
    void onDisconnect(gloox::ConnectionError e);

/*}}}*/

  private:
    static void *_run(void *rawThat);

    gloox::Client &_client;
    const unsigned int _interval;
    const unsigned int _timeout;

    pthread_t _thread;
    pthread_mutex_t _mutex;
    pthread_cond_t _cond;

    volatile bool _isWaiting;
    volatile bool _stopThread;
};

#endif // KEEPALIVE_HXX

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
