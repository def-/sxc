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

#ifndef DATETIME_HXX
#define DATETIME_HXX

// INCLUDES/*{{{*/

#include <ctime>
#include "Timestamp.hxx"

/*}}}*/

namespace Time
{
    class DateTime
    {
        public:
            DateTime();
            virtual ~DateTime();
            virtual void set(int year, int month, int day,
                             int hours=0, int minutes=0, int seconds=0);
            virtual void set(const Timestamp &ts);
            virtual const Timestamp &getTimestamp() const;
            virtual const struct tm *raw() const;

        protected:
            virtual struct tm *_fromTimestamp(const Timestamp &ts) const = 0;
            virtual Timestamp _createTimestamp(struct tm *timeinfo) const = 0;

        private:
            Timestamp _timestamp;
            struct tm *_tm;
    };
}

#endif // DATETIME_HXX

// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
