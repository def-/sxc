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

// INCLUDES/*{{{*/

#ifdef HAVE_CONFIG_H
#   include <config.hxx>
#   include <print.hxx>
#endif

#include <string>
#include <Control/Control.hxx>
#include <Control/File/Output.hxx>
#include <Time/Timestamp.hxx>
#include <Time/LocalDateTime.hxx>
#include <Time/IsoDateTimeFormat.hxx>

/*}}}*/

namespace Control
{
    namespace File
    {
        Output::Output(Control::Control &control)/*{{{*/
        : _control(&control)
        {
        }

/*}}}*/
        std::string Output::_createPath() const/*{{{*/
        {
            return _control->getJid().bare() + "/out";
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
