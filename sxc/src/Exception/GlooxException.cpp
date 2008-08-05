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

#include <Exception/GlooxException.h>

/*}}}*/


namespace Exception
{
    GlooxException::GlooxException(Type type, std::string message)/*{{{*/
    : Exception(type, message)
    {
    }/*}}}*/

    void GlooxException::createDescription() throw()/*{{{*/
    {
        switch (_type) {
            case Connection:
                _description = "Connection error: " + _message;
                break;
            case Registration:
                _description = "Registration error: " + _message;
                break;
            case PrivacyList:
                _description = "Privacy list error: " + _message;
                break;
            case SessionCreate:
                _description = "Session establishment error: " + _message;
                break;
            case Stanza:
                _description = "Stanza error: " + _message;
                break;
            case Stream:
                _description = "Stream error: " + _message;
                break;
            default:
                setInvalid();
        }
    }/*}}}*/
}

// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
