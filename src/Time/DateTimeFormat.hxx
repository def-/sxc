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

#ifndef DATETIMEFORMAT_HXX
#define DATETIMEFORMAT_HXX

// INCLUDES/*{{{*/

#include <string>
#include "DateTime.hxx"

/*}}}*/

namespace Time
{
  /**
   * @brief Formats a DateTime object.
   *
   * Basically wraps around strftime() of time.h but aims to be more secure and
   * convenient.
   */
  class DateTimeFormat
  {
    public:
      // DateTimeFormat(const DateTime *dateTime);/*{{{*/

      /**
       * @brief Initializes the formatter to the given date and time.
       * @param dateTime The date and time to be used when formatting.
       */
      DateTimeFormat(const DateTime *dateTime);

/*}}}*/
      // virtual ~DateTimeFormat();/*{{{*/

      /**
       * @brief Virtual destructor.
       */
      virtual ~DateTimeFormat();

/*}}}*/
      // virtual const std::string &string() const;/*{{{*/

      /**
       * @brief Returns a cached string which contains the result of format()
       * @return Cached string. format() has to be called first.
       */
      virtual const std::string &string() const;

/*}}}*/
      // virtual std::string format(const std::string&, unsigned int=50);/*{{{*/

      /**
       * @brief Formats the date set in the constructor.
       *
       * @warning You really want @a length to be at least of the size of the
       * resulting string.
       *
       * @param format The formatstring to be passed to strftime() in time.h.
       * @param length The buffer to use for this string.
       * @return Formatted string containing the date and time.
       */
      virtual std::string format(const std::string &format,
                     unsigned int length=50);

/*}}}*/

    private:
      // const DateTime *_dateTime;/*{{{*/

      /// The DateTime to format.
      const DateTime *_dateTime;

/*}}}*/
      // std::string _formatted;/*{{{*/

      /// Cache for the string returned by format().
      std::string _formatted;

/*}}}*/
  };
}

#endif // DATETIMEFORMAT_HXX

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
