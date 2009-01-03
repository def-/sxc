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



#ifndef ACCOUNT_LOGHANDLER_HXX
#define ACCOUNT_LOGHANDLER_HXX


// INCLUDE/*{{{*/

#include <string>

#include <gloox/gloox.h>
#include <gloox/loghandler.h>

/*}}}*/

/**
 * @brief Handle debug messages between gloox and the server.
 */
class LogHandler : public gloox::LogHandler
{
  //void handleLog(LogLevel level, LogArea area, const string &msg);/*{{{*/

  /**
   */
  void handleLog(
    gloox::LogLevel level,
    gloox::LogArea area,
    const std::string &message);

/*}}}*/
};

#endif // ACCOUNT_LOGHANDLER_HXX
// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
