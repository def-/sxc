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


#ifndef OPTION_OPTION_CPP
#define OPTION_OPTION_CPP


// INCLUDE/*{{{*/

#include <sstream>
#include <gloox/jid.h>

#include "OptionImplementation.h"
#include "Parser.h"

/*}}}*/

namespace Option
{
    template <> Option<bool>::Option(/*{{{*/
        Parser *parser,
        char shortName,
        std::string longName,
        std::string variable,
        std::string description,
        bool defaultValue)
    : OptionBase(
        shortName,
        longName,
        variable,
        description,
        false, // Booleans require no argument.
        false), // Has an default value, so it must not be set.
        _value(defaultValue)
    {
        parser->addOption(this);
    }/*}}}*/

    template <> Option<bool>::Option(/*{{{*/
        Parser *parser,
        char shortName,
        std::string longName,
        std::string variable,
        std::string description)
    : OptionBase( // To use getName().
        shortName,
        longName,
        variable,
        description,
        false,
        false),
        _value(false) // Default to false.
    {
        parser->addOption(this);
    }/*}}}*/

    template <> void Option<bool>::doSetValue(std::string rawValue)/*{{{*/
    {
        _isSet = true;
        _value = !_value; // Complement the value.
    }/*}}}*/

    template <> void Option<char>::doSetValue(std::string rawValue)/*{{{*/
    {
        if (rawValue.length() != 1)
            throw Exception::OptionException(
                Exception::ValueInvalid, getName());
        _value = rawValue.at(0);
    }/*}}}*/
}


#endif //OPTION_OPTION_CPP

// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
