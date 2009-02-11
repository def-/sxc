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

#ifndef TIMESTAMP_HXX
#define TIMESTAMP_HXX

#include <ctime>

/**
 * @brief Contains the DateTime library.
 *
 * The DateTime library provides functionality to deal with timestamps and
 * dates in a more convenient and secure fashion than the C library time.h.
 */
namespace Time
{
  /**
   * @brief Represents an UNIX timestamp.
   *
   * Basic type for the usage of this DateTime library. Resembles an UNIX
   * timestamp whose value can not be altered if set once. Hence, an object of
   * Timestamp will always contain an UNIX timestamp that is not modifyable.
   */
  class Timestamp
  {
    public:
      // Timestamp();/*{{{*/

      /**
       * @brief Default constructor, makes a snapshot of current time.
       *
       * Stores the current UNIX timestamp as returned by time() of time.h.
       */
      Timestamp();

/*}}}*/
      // Timestamp(time_t time);/*{{{*/

      /**
       * @brief Constructor to initialize object to a specific timestamp value.
       * @param time The value of an UNIX timestamp.
       */
      Timestamp(time_t time);

/*}}}*/
      // virtual ~Timestamp();/*{{{*/

      /**
       * @brief Virtual destructor.
       */
      virtual ~Timestamp();

/*}}}*/
      // virtual const time_t &raw() const;/*{{{*/

      /**
       * @brief Returns the value of this timestamp.
       * @return The raw value of this timestamp.
       */
      virtual const time_t &raw() const;

/*}}}*/

    private:
      // time_t _raw;/*{{{*/

      /// The raw value of this timestamp.
      time_t _raw;

/*}}}*/
  };
}

#endif // TIMESTAMP_HXX

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
