#line 2 "sxc:setupClient.cxx"
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

#include <gloox/client.h>
#include <gloox/disco.h>
#include <gloox/delayeddelivery.h>
#include <gloox/receipt.h>

#include <setupClient.hxx>

#include <libsxc/Debug/Logger.hxx>

/*}}}*/

void setupClient(/*{{{*/
  gloox::Client &client,
  const std::string &name,
  const std::string &version)
{
  // "console" is not exactly what sxc is, but "pc" is described as a
  // full-featured GUI.
  const std::string category = "client";
  const std::string type = "console";

  LOG(
    "Set identity: (category: \"" + category + "\", type: \"" +
    type + "\", name: \"" + name + "\").");

  client.disco()->setIdentity(category, type, name);

  LOG(
    "Set version: (name: \"" + name + "\", version: \"" +
    version + "\").");

  client.disco()->setVersion(name, version);

  // Has to be registered, so delayed deliveries can be handled.
  client.registerStanzaExtension(new gloox::DelayedDelivery());

  std::string features;
  for (gloox::StringList::const_iterator i =
  client.disco()->features().begin();
  i != client.disco()->features().end();
  ++i) {
    features += *i + ", ";
  }
  if (2 <= features.length())
    features.erase(features.end() - 2); // Remove last ", "
  LOG("Features to be announced: " + features);
}/*}}}*/

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
