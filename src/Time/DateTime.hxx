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
  /**
   * @brief Abstract representation of date and time.
   *
   * Derived classes have to implement methods for the creation of a concrete
   * date from a Timestamp and vice-versa. This class provides an interface to
   * set a date via raw values or a Timestamp which are then translated into a
   * specific date and time, according to the timezone handled in the pure
   * virtual methods.
   */
  class DateTime
  {
    public:
      // DateTime();/*{{{*/

      /**
       * @brief Default constructor.
       * @note  See set() for how to really set date and time.
       */
      DateTime();

/*}}}*/
      // virtual ~DateTime();/*{{{*/

      /**
       * @brief Virtual destructor.
       */
      virtual ~DateTime();

/*}}}*/
      // virtual void set(int, int, int, int=0, int=0, int=0);/*{{{*/

      /**
       * @brief Sets a timestamp and date.
       *
       * @note The values are treated according to the timezone the derived
       * class represents.
       *
       * @param year    The year to represent.
       * @param month   The month to represent.
       * @param day     The number of day in the month to represent.
       * @param hours   The hour of that day.
       * @param minutes The minutes of that hour.
       * @param seconds The seconds of that minute.
       */
      virtual void set(int year, int month, int day,
               int hours=0, int minutes=0, int seconds=0);

/*}}}*/
      // virtual void set(const Timestamp &ts);/*{{{*/

      /**
       * @brief Sets a date based on the supplied timestamp.
       *
       * The value is calculated regarding the timezone which this class
       * represents.
       *
       * @param ts The timestamp to initialize the date and time.
       */
      virtual void set(const Timestamp &ts);

/*}}}*/
      // virtual const Timestamp &getTimestamp() const;/*{{{*/

      /**
       * @brief Returns the timestamp belonging to this date and time.
       * @return Timestamp belonging to this DateTime representation.
       */
      virtual const Timestamp &getTimestamp() const;

/*}}}*/
      // virtual const struct tm *raw() const;/*{{{*/

      /**
       * @brief Returns a raw value containing time and date information.
       * @note This is a broken-down representation as used in time.h.
       * @return Raw, broken-down date and time representation.
       */
      virtual const struct tm *raw() const;

/*}}}*/

    protected:
      // virtual struct tm *_fromTimestamp(const Timestamp &ts) const = 0;/*{{{*/

      /**
       * @brief Pure virtual method to create a localized date and time.
       *
       * The date and time returned shall be dependant on a specific timezone
       * which this class shall represent.
       *
       * @param ts The timestamp from which to calculate date and time.
       * @return Broken-down date and time information as used in time.h.
       */
      virtual struct tm *_fromTimestamp(const Timestamp &ts) const = 0;

/*}}}*/
      // virtual Timestamp _createTimestamp(struct tm *timeinfo) const = 0;/*{{{*/

      /**
       * @brief Calculates the value of a timestamp.
       *
       * Value shall be calculated depending on the timezone this class shall
       * represent.
       *
       * @param timeinfo Raw, broken-down date and time information (time.h)
       * @return A Timestamp representing the same date.
       */
      virtual Timestamp _createTimestamp(struct tm *timeinfo) const = 0;

/*}}}*/

    private:
      // Timestamp _timestamp;/*{{{*/

      /// The Timestamp describing this date and time.
      Timestamp _timestamp;

/*}}}*/
      // struct tm *_tm;/*{{{*/

      /// The date and time described by the Timestamp.
      struct tm *_tm;

/*}}}*/
  };
}

#endif // DATETIME_HXX

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
