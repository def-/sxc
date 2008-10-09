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

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
