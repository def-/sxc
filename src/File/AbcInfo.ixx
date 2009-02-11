#line 2 "sxc:File/AbcInfo.ixx"
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

#ifndef FILE_ABCINFO_IXX
#define FILE_ABCINFO_IXX

// INCLUDE/*{{{*/

#ifdef HAVE_CONFIG_H
# include <config.hxx>
#endif

#include <fstream>
#include <string>
#include <sstream>

#include <gloox/presence.h>

#include <Account/RosterType.hxx>

#include <libsxc/Debug/Logger.hxx>

/*}}}*/

namespace File
{
  template <typename T> void AbcInfo::_set(const std::string &key, T &value)/*{{{*/
  {
    if (_isRemoved)
      return;
    std::ostringstream ss;
    ss << "Setting info: (path: \"" << _path << "\", key: \"" << key
       << "\", value: \"" << value << "\").";
    LOG(ss.str());
    // FIXME: Is it reasonable to open and close file every time something changes?
    // Discard current conent before filling in new.
    std::ofstream file((_path + key).c_str(), std::ios::trunc);
    file << value << std::endl;
    // File gets claused automatically.
  }/*}}}*/

  template <> inline void AbcInfo::_set(/*{{{*/
    const std::string &key,
    gloox::Presence::PresenceType &value)
  {
    std::string text;

    switch (value) {
    case gloox::Presence::Available:
      text = "available";
      break;
    case gloox::Presence::Chat:
      text = "chat";
      break;
    case gloox::Presence::Away:
      text = "away";
      break;
    case gloox::Presence::DND:
      text = "busy";
      break;
    case gloox::Presence::XA:
      text = "xaway";
      break;
    case gloox::Presence::Unavailable:
      text = "offline";
      break;
    case gloox::Presence::Probe:
      text = "probe";
      break;
    case gloox::Presence::Error:
      text = "error";
      break;
    default:
      text = "unknown";
    }

    _set(key, text);
  }/*}}}*/
  template <> inline void AbcInfo::_set(/*{{{*/
    const std::string &key,
    Account::RosterType &value)
  {
    std::string text;

    switch (value) {
    case Account::Local:
      text = "local";
      break;
    case Account::Remote:
      text = "remote";
      break;
    default:
      text = "unknown";
    }

    _set(key, text);
  }/*}}}*/
}

#endif // FILE_ABCINFO_IXX
// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
