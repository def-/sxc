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

#ifndef PING_HANDLER_HXX
#define PING_HANDLER_HXX

// INCLUDES/*{{{*/

#include <string>

#include <pthread.h>

#include <gloox/eventhandler.h>

#include <Ping/ResultHandler.hxx>

/*}}}*/

namespace Ping
{
  /**
   * Handle responses (pongs) to outgoing pings.
   */
  class Handler : public gloox::EventHandler
  {
    public:
      //Handler(ResultHandler *handler, unsigned int timeoutSeconds = 1);/*{{{*/

      /**
       * Create a ping handler.
       *
       * @note For the sake of simplicity the object will remain existant until
       *       the @ref timeoutSeconds are over. It will still call the @ref
       *       ResultHandler immediately if a response comes in.
       */
      Handler(ResultHandler *handler, unsigned int timeoutSeconds = 1);

/*}}}*/
      //void run();/*{{{*/

      /**
       * Run the thread. Only to be called once. Alle further calls are noop.
       * The thread will automatically delete the object as soon as the timeout
       * is reached.
       */
      void run();

/*}}}*/
      //void handleEvent(const gloox::Event &event);/*{{{*/

      /**
       * Handle responses (pongs) to pings that were sent before.
       */
      void handleEvent(const gloox::Event &event);

/*}}}*/

    private:
      void _handleResult(Result result);
      static void *_run(void *rawThat);

      unsigned int _timeoutSeconds;
      ResultHandler *_handler;
      pthread_t _thread;
      pthread_mutex_t *_mutex;
      bool _isAnswered;
  };
}

#endif // PING_HANDLER_HXX

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
