#line 2 "sxc:Contact/File/Info.ixx"
// LICENSE/*{{{*/
/*
  sxc
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

#ifndef CONTACT_FILE_INFO_IXX
#define CONTACT_FILE_INFO_IXX

// INCLUDE/*{{{*/

#ifdef HAVE_CONFIG_H
# include <config.hxx>
#endif

/*}}}*/

namespace Contact
{
  namespace File
  {
    template <typename T> void Info::setPresence(T &value)/*{{{*/
    {
      _set("presence", value);
    }/*}}}*/
    template <typename T> void Info::setMessage(T &value)/*{{{*/
    {
      _set("message", value);
    }/*}}}*/
    template <typename T> void Info::setRoster(T &value)/*{{{*/
    {
      _set("roster", value);
    }/*}}}*/
  }
}

#endif // CONTACT_FILE_INFO_IXX
// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
