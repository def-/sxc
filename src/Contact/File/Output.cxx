#line 2 "sxc:Contact/File/Output.cxx"
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
#include <sstream>

#include <Contact/File/Output.hxx>
#include <Time/Timestamp.hxx>
#include <Time/LocalDateTime.hxx>
#include <Time/IsoDateTimeFormat.hxx>

#include <libsxc/Debug/Logger.hxx>

/*}}}*/

namespace Contact
{
  namespace File
  {
    Output::Output(const std::string &accountJid, const std::string &contactJid)/*{{{*/
    : _accountJid(accountJid)
    , _contactJid(contactJid)
    {
      initialize();
      open();
    }/*}}}*/
    Output::~Output()/*{{{*/
    {
      close();
    }/*}}}*/
    void Output::writeOutgoing(std::string message)/*{{{*/
    {
      write(_indent(_format("<" + _accountJid + "> "), message) + "\n");
    }/*}}}*/
    void Output::writeIncomming(std::string message)/*{{{*/
    {
      write(_indent(_format("<" + _contactJid + "> "), message) + "\n");
    }/*}}}*/

    std::string Output::_createPath() const/*{{{*/
    {
      return _accountJid + '/' + _contactJid + "/out";
    }/*}}}*/
    std::string Output::_format(const std::string &output) const/*{{{*/
    {
      Time::LocalDateTime date = Time::LocalDateTime(Time::Timestamp());
      Time::IsoDateTimeFormat format(&date);
      return format.string() + ' ' + output;
    }/*}}}*/
    std::string Output::_indent(const std::string &prefix, std::string &text) const/*{{{*/
    {
      size_t pos = 0;
      while (true) {
        pos = text.find('\n', pos);

        std::ostringstream ss;
        ss << "Found newline (pos: " << pos << ", size: " << text.size() << ").";
        LOG2(ss.str());

        if (std::string::npos == pos)
          return prefix + text;

        text.insert(pos + 1, std::string(prefix.size(), ' '));

        pos += prefix.size() + 1;
      }
    }/*}}}*/
    //std::string Output::_indent(const std::string &prefix, std::string &text) const/*{{{*/
    //{
    //  size_t pos = 0;
    //  while (true) {
    //    pos = text.find('\n', pos);

    //    std::ostringstream ss;
    //    ss << "Found newline (pos: " << pos << ", size: " << text.size() << ").";
    //    LOG2(ss.str());

    //    if (std::string::npos == pos)
    //      return prefix + text;

    //    text.insert(pos + 1, std::string(prefix.size(), ' '));

    //    pos += prefix.size() + 1;
    //  }
    //}/*}}}*/
  }
}

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
