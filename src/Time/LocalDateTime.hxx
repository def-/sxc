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

#ifndef LOCALDATETIME_HXX
#define LOCALDATETIME_HXX

#include "DateTime.hxx"

namespace Time
{
    class LocalDateTime : public DateTime
    {
        public:
            LocalDateTime(const Timestamp &ts);
            LocalDateTime(int year, int month, int day,
                          int hour, int minutes, int seconds);
            virtual ~LocalDateTime();

        protected:
            virtual struct tm *_fromTimestamp(const Timestamp &ts) const;
            virtual Timestamp _createTimestamp(struct tm *tm) const;
    };
}

#endif // LOCALDATETIME_HXX

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
