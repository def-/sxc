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

// INCLUDES /*{{{*/

#include <ctime>
#include <stdexcept>
#include "DateTime.hxx"

/*}}}*/

namespace Time
{
DateTime::DateTime()/*{{{*/
: _tm(NULL)
{
}

/*}}}*/
DateTime::~DateTime()/*{{{*/
{
}

/*}}}*/
void DateTime::set(int year, int month, int day,
                   int hours, int minutes, int seconds)/*{{{*/
{
    {
        struct tm *tm = _fromTimestamp(Timestamp());
        tm->tm_year  = year - 1900;
        tm->tm_mon   = month - 1;
        tm->tm_mday  = day;
        tm->tm_hour  = hours;
        tm->tm_min   = minutes;
        tm->tm_sec   = seconds;
        tm->tm_isdst = -1;

        _tm = tm;
    }
    _timestamp = _createTimestamp(_tm);
}

/*}}}*/
void DateTime::set(const Timestamp &ts)/*{{{*/
{
    _timestamp = ts;
    _tm = _fromTimestamp(ts);
}

/*}}}*/
const Timestamp &DateTime::getTimestamp() const/*{{{*/
{
    return _timestamp;
}

/*}}}*/
const struct tm *DateTime::raw() const/*{{{*/
{
    if (NULL == _tm) {
        throw std::logic_error("_tm not set");
    }
    return _tm;
}

/*}}}*/
}

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
