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

#include <string>
#include "IsoDateTimeFormat.hxx"

/*}}}*/

namespace Time
{
  IsoDateTimeFormat::IsoDateTimeFormat(const DateTime *dateTime, unsigned short formatOptions)/*{{{*/
  : DateTimeFormat(dateTime)
  {
    std::string formatstr;
    if (formatOptions & FORMAT_DATE    == FORMAT_DATE)
      formatstr.append("%FT");
    if (formatOptions & FORMAT_SECONDS == FORMAT_SECONDS)
      formatstr.append("%T");
    else
      formatstr.append("%R");

    format(formatstr);
  }

  /*}}}*/
  IsoDateTimeFormat::~IsoDateTimeFormat()/*{{{*/
  {
  }

  /*}}}*/
  std::string IsoDateTimeFormat::format(const std::string &format,
                      unsigned int length)/*{{{*/
  {
    return DateTimeFormat::format(format, length);
  }

  /*}}}*/
}

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
