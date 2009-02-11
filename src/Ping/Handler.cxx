#line 2 "sxc:Ping/Handler.cxx"
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

// INCLUDES/*{{{*/

#ifdef HAVE_CONFIG_H
# include <config.hxx>
#endif

#include <string>

#include <pthread.h>
#include <unistd.h>

#include <gloox/event.h>

#include <libsxc/Debug/Logger.hxx>

#include <Ping/Handler.hxx>
#include <Ping/ResultHandler.hxx>

/*}}}*/

namespace Ping
{
  Handler::Handler(ResultHandler *handler, unsigned int timeoutSeconds)/*{{{*/
  : _timeoutSeconds(timeoutSeconds)
  , _thread(0)
  , _mutex(new pthread_mutex_t)
  , _handler(handler)
  , _isAnswered(false)
  {
    pthread_mutex_init(_mutex, NULL);
  }/*}}}*/

  void Handler::run()/*{{{*/
  {
    if (!_thread)
      pthread_create(&_thread, NULL, _run, (void*)this);
  }/*}}}*/
  void Handler::handleEvent(const gloox::Event &event)/*{{{*/
  {
    std::string strEvent;
    Result result;

    switch (event.eventType()) {
    case gloox::Event::PingPing:
      result = Error;
      strEvent = "Ping";
      break;
    case gloox::Event::PingPong:
      result = Pong;
      strEvent = "Pong";
      break;
    case gloox::Event::PingError:
      result = Error;
      strEvent = "Error";
      break;
    default:
      strEvent = "Unknown";
    }

    LOG("Received event: " + strEvent + ".");
    _handleResult(result);
  }/*}}}*/

  void Handler::_handleResult(Result result)/*{{{*/
  {
    pthread_mutex_lock(_mutex);

    if (!_isAnswered) {
      _isAnswered = true;
      _handler->handlePingResult(result);
    }

    pthread_mutex_unlock(_mutex);
  }/*}}}*/
  void *Handler::_run(void *rawThat)/*{{{*/
  {
    LOG("Start Handler thread.");
    Handler *that = (Handler *) rawThat;

    sleep(that->_timeoutSeconds);
    LOG("Timed out");
    that->_handleResult(Timeout);
    delete that;

    LOG("Stop Handler thread.");
    return (void *) NULL;
  }/*}}}*/
}

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
