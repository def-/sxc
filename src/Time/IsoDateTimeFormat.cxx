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
