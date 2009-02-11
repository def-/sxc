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

#ifndef ISODATETIMEFORMAT_HXX
#define ISODATETIMEFORMAT_HXX

// INCLUDES/*{{{*/

#include <string>
#include "DateTimeFormat.hxx"

/*}}}*/

namespace Time
{
  /**
   * @brief Formatter according to the ISO 8601 standard.
   */
  class IsoDateTimeFormat : public DateTimeFormat
  {
    public:
      // static const unsigned short FORMAT_DATE    = 0x1;/*{{{*/

      /// Bitmask value to enable formatting of the date.
      static const unsigned short FORMAT_DATE    = 0x1;

/*}}}*/
      // static const unsigned short FORMAT_SECONDS = 0x2;/*{{{*/

      /// Bitmask value to enable formatting of the seconds.
      static const unsigned short FORMAT_SECONDS = 0x2;

/*}}}*/
      // IsoDateTimeFormat(const DateTime*, unsigned short);/*{{{*/

      /**
       * @brief Constructs this object.
       *
       * Directly formats the passed date which then can be obtained by calling
       * string().
       *
       * @param dateTime The date and time to represent.
       * @param formatOptions Bitmask which parts of the DateTime to format.
       */
      IsoDateTimeFormat(const DateTime *dateTime,
        unsigned short formatOptions=(FORMAT_DATE | FORMAT_SECONDS));

/*}}}*/
      // ~IsoDateTimeFormat();/*{{{*/

      /**
       * @brief Nonvirtual destructor. Do not inherit.
       */
      ~IsoDateTimeFormat();

/*}}}*/

    private:
      // std::string format(const std::string &format, unsigned int length=50);/*{{{*/

      /// Make format() private so that the date can not be re-formatted.
      std::string format(const std::string &format, unsigned int length=50);


/*}}}*/
  };
}

#endif // ISODATETIMEFORMAT_HXX

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
