#line 2 "sxc:Subscriptions.cxx"
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

#ifdef HAVE_CONFIG_H
# include <config.hxx>
#endif

#include <string>

#include <gloox/gloox.h>

#include <Subscriptions.hxx>

/*}}}*/

const std::string subTypeToUser(gloox::SubscriptionType type)/*{{{*/
{
  std::string user;
  switch (type) {
  case gloox::S10nNone:
    user = "no";
    break;
  case gloox::S10nNoneOut:
    user = "requested";
    break;
  case gloox::S10nNoneIn:
    user = "no";
    break;
  case gloox::S10nNoneOutIn:
    user = "requested";
    break;
  case gloox::S10nTo:
    user = "yes";
    break;
  case gloox::S10nToIn:
    user = "yes";
    break;
  case gloox::S10nFrom:
    user = "no";
    break;
  case gloox::S10nFromOut:
    user = "requested";
    break;
  case gloox::S10nBoth:
    user = "yes";
    break;
  default:
    user = "unknown";
    break;
  }

  return user;
}/*}}}*/
const std::string subTypeToContact(gloox::SubscriptionType type)/*{{{*/
{
  std::string contact;
  switch (type) {
  case gloox::S10nNone:
    contact = "no";
    break;
  case gloox::S10nNoneOut:
    contact = "no";
    break;
  case gloox::S10nNoneIn:
    contact = "requested";
    break;
  case gloox::S10nNoneOutIn:
    contact = "requested";
    break;
  case gloox::S10nTo:
    contact = "no";
    break;
  case gloox::S10nToIn:
    contact = "requested";
    break;
  case gloox::S10nFrom:
    contact = "yes";
    break;
  case gloox::S10nFromOut:
    contact = "yes";
    break;
  case gloox::S10nBoth:
    contact = "yes";
    break;
  default:
    contact = "unknown";
    break;
  }

  return contact;
}/*}}}*/

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
