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

#ifndef LOCALDATETIME_HXX
#define LOCALDATETIME_HXX

#include "DateTime.hxx"

namespace Time
{
  /**
   * @brief A representation of a locally interpreted date and time.
   *
   * Timestamps passed and dates set manually will always be interpreted as
   * local dates, which means according to any timezone that your system is set
   * to.
   */
  class LocalDateTime : public DateTime
  {
    public:
      // LocalDateTime(const Timestamp &ts);/*{{{*/

      /**
       * @brief Default constructor, calls DateTime::set().
       * @param ts The timestamp to initialize this object to.
       */
      LocalDateTime(const Timestamp &ts);

/*}}}*/
      // LocalDateTime(int, int, int, int, int, int);/*{{{*/

      /**
       * @brief Initializes this object by calling DateTime::set()
       * @see DateTime::set()
       */
      LocalDateTime(int year, int month, int day,
              int hour, int minutes, int seconds);

/*}}}*/
      // virtual ~LocalDateTime();/*{{{*/

      /**
       * @brief Virtual destructor.
       */
      virtual ~LocalDateTime();

/*}}}*/

    protected:
      // virtual struct tm *_fromTimestamp(const Timestamp &ts) const;/*{{{*/

      /// @see DateTime::_fromTimestamp()
      virtual struct tm *_fromTimestamp(const Timestamp &ts) const;

/*}}}*/
      // virtual Timestamp _createTimestamp(struct tm *tm) const;/*{{{*/

      /// @see DateTime::_createTimestamp()
      virtual Timestamp _createTimestamp(struct tm *tm) const;

/*}}}*/
  };
}

#endif // LOCALDATETIME_HXX

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
