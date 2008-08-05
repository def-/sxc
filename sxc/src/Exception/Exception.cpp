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

#include <Exception/Exception.h>
#include <Exception/Type.h>

/*}}}*/

namespace Exception
{
    Exception::Exception(Type type, std::string &message) throw()/*{{{*/
    : _type(type), _message(message), _isDescriptionCreated(false)
    {
    }/*}}}*/

    Exception::Exception(Type type, const char *message) throw()/*{{{*/
    : _type(type), _isDescriptionCreated(false)
    {
        _message = *message;
    }/*}}}*/

    Exception::~Exception() throw()/*{{{*/
    {
    }/*}}}*/

    const std::string &Exception::getMessage() const throw()/*{{{*/
    {
        return _message;
    }/*}}}*/

    const std::string &Exception::getDescription() throw()/*{{{*/
    {
        if (!_isDescriptionCreated) {
            createDescription();
            _isDescriptionCreated = true;
        }
        return _description;
    }/*}}}*/

    void Exception::setInvalid() throw()/*{{{*/
    {
        _description = "Invalid exception type.";
    }/*}}}*/

    Type Exception::getType() const throw()/*{{{*/
    {
        return _type;
    }/*}}}*/

    const char *Exception::what() const throw()/*{{{*/
    {
        return getMessage().c_str();
    }/*}}}*/
}

// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
