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


#ifndef OPTION_OPTION_IXX
#define OPTION_OPTION_IXX


// INCLUDE/*{{{*/

#include <vector>
#include <string>
#include <sstream>

#include <gloox/jid.h>

#include <Exception/OptionException.hxx>

/*}}}*/

namespace Option
{
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
        true) // Has no default value, so it is obligatory.
    {
        parser->addOption(this);
    }/*}}}*/
    template <> inline Option<bool>::Option(/*{{{*/
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

    template <typename T> void Option<T>::setValue(std::string rawValue)/*{{{*/
    {
        if (_isSet) // Only allow to be set one time.
            throw Exception::OptionException(
                Exception::OptionSetMultiple, getName());

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
            throw Exception::OptionException(
                Exception::ValueInvalid, getName());
    }/*}}}*/
    template <> inline void Option<bool>::doSetValue(std::string rawValue)/*{{{*/
    {
        _isSet = true;
        _value = !_value; // Complement the value.
    }/*}}}*/
    template <> inline void Option<char>::doSetValue(std::string rawValue)/*{{{*/
    {
        if (rawValue.length() != 1)
            throw Exception::OptionException(
                Exception::ValueInvalid, getName());
        _value = rawValue.at(0);
    }/*}}}*/
    template <> inline void Option<gloox::JID>::doSetValue(std::string rawValue)/*{{{*/
    {
        if (!_value.setJID(rawValue)
        || _value.username().empty()
        || _value.server().empty())
            throw Exception::OptionException(
                Exception::JidInvalid,
                _value.full());
    }/*}}}*/
    template <typename T> T Option<T>::getValue()/*{{{*/
    {
        return _value;
    }/*}}}*/
}


#endif // OPTION_OPTION_IXX
// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
