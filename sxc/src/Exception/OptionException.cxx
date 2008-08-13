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

/* $Id$ */

// INCLUDE/*{{{*/

#include <string>

#include <Exception/OptionException.hxx>

#ifdef HAVE_CONFIG_H
#   include <config.hxx>
#endif

/*}}}*/


namespace Exception
{
    OptionException::OptionException(Type type, std::string message)/*{{{*/
    : Exception(type, message)
    {
    }/*}}}*/

    void OptionException::createDescription() throw()/*{{{*/
    {
        switch (_type) {
            case ShowUsage:
                _description =
                std::string(PACKAGE) + " " + VERSION + " (C) " + COPYRIGHT;
                break;
            case OptionNotSet:
                _description =
                "Obligatory option " + _message + " not set";
                break;
            case OptionUnknown:
                _description = "Unknown option " + _message;
                break;
            case ValueNotSet:
                _description = "Option " + _message + " requires a value";
                break;
            case PortInvalid:
                _description = "Invalid port " + _message;
                break;
            case JidInvalid:
                _description = "Invalid JID " + _message;
                break;
            case ValueInvalid:
                _description = "Invalid value for " + _message;
                break;
            case OptionsConflicting:
                _description = "Option " + _message + " set more than one time";
                break;
            default:
                setInvalid();
        }
    }/*}}}*/
}

// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
