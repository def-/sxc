// LICENSE/*{{{*/
/*
  sxc - Simple Xmpp Client
  Copyright (C) 2008 Dennis Felsing, Andreas Waidler

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
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

// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
