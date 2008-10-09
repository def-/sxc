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

#ifndef ISODATETIMEFORMAT_HXX
#define ISODATETIMEFORMAT_HXX

// INCLUDES/*{{{*/

#include <string>
#include "DateTimeFormat.hxx"

/*}}}*/

namespace Time
{
    class IsoDateTimeFormat : public DateTimeFormat
    {
        public:
            static const unsigned short FORMAT_DATE    = 0x1;
            static const unsigned short FORMAT_SECONDS = 0x2;
            IsoDateTimeFormat(const DateTime *dateTime,
                unsigned short formatOptions=(FORMAT_DATE | FORMAT_SECONDS));
            ~IsoDateTimeFormat();
        private:
            std::string format(const std::string &format, unsigned int length=50);
    };
}

#endif // ISODATETIMEFORMAT_HXX

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
