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

// INCLUDES/*{{{*/

#ifdef HAVE_CONFIG_H
#   include <config.hxx>
#   include <print.hxx>
#endif

#include <string>
#include <Control/Control.hxx>
#include <Contact/Contact.hxx>
#include <Contact/File/Output.hxx>
#include <Time/Timestamp.hxx>
#include <Time/LocalDateTime.hxx>
#include <Time/IsoDateTimeFormat.hxx>

/*}}}*/

namespace Contact
{
    namespace File
    {
        Output::Output(Control::Control &control, Contact &contact)/*{{{*/
        : _control(&control)
        , _contact(&contact)
        {
        }

/*}}}*/
        std::string Output::_createPath() const/*{{{*/
        {
            return _control->getJid().bare() + '/'
                   + _contact->getJid().bare() + "/out";
        }

/*}}}*/
        std::string Output::_format(const std::string &output) const/*{{{*/
        {
            Time::LocalDateTime date = Time::LocalDateTime(Time::Timestamp());
            Time::IsoDateTimeFormat format(&date);
            return format.string() + ' ' + output;
        }

/*}}}*/
    }
}

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
