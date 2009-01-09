#line 2 "sxc:Contact/File/Info.cxx"
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

#include <Contact/File/Info.hxx>

/*}}}*/

namespace Contact
{
  namespace File
  {
    Info::Info(const std::string &accountJid, const std::string &contactJid)/*{{{*/
    : _accountJid(accountJid)
    , _contactJid(contactJid)
    {
      initialize();
      _reset();
    }/*}}}*/
    Info::~Info()/*{{{*/
    {
      _reset();
    }/*}}}*/

    void Info::remove()/*{{{*/
    {
      _removeFile("presence");
      _removeFile("message");
      _removeFile("roster");
      ::File::AbcInfo::remove();
    }/*}}}*/

    const std::string Info::_createPath()/*{{{*/
    {
      return _accountJid + "/" + _contactJid + "/nfo/";
    }/*}}}*/
    void Info::_reset()/*{{{*/
    {
      setPresence("offline");
      setMessage("");
    }/*}}}*/
  }
}

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
