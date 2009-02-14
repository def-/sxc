#line 2 "sxc:KeepAlive.cxx"
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

#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

#include <gloox/event.h>

#include <libsxc/Debug/Logger.hxx>

#include <KeepAlive.hxx>

/*}}}*/

KeepAlive::KeepAlive(
  gloox::Client &client,
  unsigned int interval,
  unsigned int timeout)/*{{{*/
: _client(client)
, _interval(interval)
, _timeout(timeout)
, _thread(0)
, _stopThread(false)
{
  pthread_mutex_init(&_mutex, NULL);
  pthread_cond_init(&_cond, NULL);
}/*}}}*/
KeepAlive::~KeepAlive()/*{{{*/
{
  _stopThread = true;
  pthread_cond_broadcast(&_cond);
  if (_thread)
    pthread_join(_thread, NULL);
  pthread_cond_destroy(&_cond);
  pthread_mutex_destroy(&_mutex);
}/*}}}*/

void KeepAlive::run()/*{{{*/
{
  if (!_thread)
    pthread_create(&_thread, NULL, _run, (void*)this);
}/*}}}*/
void KeepAlive::handleEvent(const gloox::Event &event)/*{{{*/
{
  if (_isWaiting) {
    _isWaiting = false;
    pthread_cond_broadcast(&_cond);
  }
}/*}}}*/

void *KeepAlive::_run(void *rawThat)/*{{{*/
{
  LOG("Start keepalive thread.");
  KeepAlive *that = (KeepAlive *) rawThat;

  struct timespec timeout;
  struct timeval tv;
  struct timezone tz;

  while (!that->_stopThread) {
    gettimeofday(&tv, &tz);
    timeout.tv_nsec = 0;

    if (gloox::StateConnected == that->_client.state()) {
      that->_isWaiting = true;
      that->_client.xmppPing(that->_client.server(), that);
      pthread_mutex_lock(&that->_mutex);
      timeout.tv_sec = tv.tv_sec + that->_timeout;

      if (that->_isWaiting) {
        LOG("Wait for pong.");
        pthread_cond_timedwait(&that->_cond, &that->_mutex, &timeout);
        LOG("Finished waiting for pong.");

        if (that->_stopThread)
          break;

        if (that->_isWaiting) {
          that->_client.disconnect();
          that->_isWaiting = false;
        }
      }

      pthread_mutex_unlock(&that->_mutex);
    }

    pthread_mutex_lock(&that->_mutex);
    // Use the first time, substracts response-waiting-time.
    timeout.tv_sec = tv.tv_sec + that->_interval;
    LOG("Wait for interval.");
    pthread_cond_timedwait(&that->_cond, &that->_mutex, &timeout);
    LOG("Finished waiting for interval.");
    pthread_mutex_unlock(&that->_mutex);
  }

  LOG("End keepalive thread.");
  return NULL;
}/*}}}*/

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
