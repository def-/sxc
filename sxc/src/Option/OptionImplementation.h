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


#ifndef OPTION_OPTIONIMPLEMENTATION_H
#define OPTION_OPTIONIMPLEMENTATION_H


// INCLUDE/*{{{*/

#include <vector>
#include <string>
#include <sstream>

#include "Option.h"

/*}}}*/

namespace Option
{
    template <typename T> Option<T>::Option(/*{{{*/
        Parser *parser,
        char shortName,
        std::string longName,
        std::string variable,
        std::string description,
        T defaultValue,
        bool isObligatory)
    : OptionBase(
        shortName,
        longName,
        variable,
        description,
        true, // All non-booleans require an argument.
        isObligatory),
        _value(defaultValue)
    {
        parser->addOption(this);
    }/*}}}*/

    template <typename T> Option<T>::Option(/*{{{*/
        Parser *parser,
        char shortName,
        std::string longName,
        std::string variable,
        std::string description,
        T defaultValue)
    : OptionBase(
        shortName,
        longName,
        variable,
        description,
        true, // All non-booleans require an argument.
        false), // Has an default value, so it must not be set.
        _value(defaultValue)
    {
        parser->addOption(this);
    }/*}}}*/

    template <typename T> Option<T>::Option(/*{{{*/
        Parser *parser,
        char shortName,
        std::string longName,
        std::string variable,
        std::string description)
    : OptionBase(
        shortName,
        longName,
        variable,
        description,
        true, // All non-booleans require an argument.
        true) // Has no default value, so it must be set.
    {
        parser->addOption(this);
    }/*}}}*/

    template <typename T> void Option<T>::setValue(std::string rawValue)/*{{{*/
    {
        if (_isSet) // Only allow to be set one time.
            throw "Option set multiple times.";

        doSetValue(rawValue);

        _isSet = true;
    }/*}}}*/

    template <typename T> void Option<T>::doSetValue(std::string rawValue)/*{{{*/
    {
        std::istringstream instream;

        instream.str(rawValue);
        instream >> _value;

        if (instream.bad() // Conversion failed
        || !instream.eof())
            throw "Conversion to correct type failed";
    }/*}}}*/

    template <typename T> T Option<T>::getValue()/*{{{*/
    {
        return _value;
    }/*}}}*/
}


#endif // OPTION_OPTIONIMPLEMENTATION_H
// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
