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


#ifndef OPTION_OPTION_H
#define OPTION_OPTION_H


// INCLUDE/*{{{*/

#include <gloox/jid.h>

#include <Option/OptionBase.h>
#include <Option/Parser.h>
#include <Exception/OptionException.h>

/*}}}*/

namespace Option
{
    /*
     * @class Option
     * @author Dennis Felsing
     * @brief A representation of an program option.
     *
     */
    template <typename T>
    class Option : public OptionBase
    {
        public:
            //Option(/*{{{*/

            /**
             * @brief Create a new option.
             *
             * Construct a new option object and add it to the parser.
             *
             * @warning This constructor takes the default value and whether
             *          the option is optional. This only makes sense when
             *          using boolean as type.
             *
             * @param parser The parser the object will be added to.
             * @param shortName A short option name. ('x' for "-x")
             * @param longName A long option name. ("foo" for --foo)
             * @param variable How to call the variable in the usage output.
             * @param description A description of the option.
             * @param defaultValue The value to be set if not specified.
             * @param isObligatory Whether the option has to be set.
             */
            Option(
                Parser *parser,
                char shortName,
                std::string longName,
                std::string variable,
                std::string description,
                T defaultValue,
                bool isObligatory);

/*}}}*/
            //Option(/*{{{*/

            /**
             * @brief Create a new option.
             *
             * Construct a new option object and add it to the parser.
             *
             * @note This constructor takes a default value, so the option is
             *       optional.
             *
             * @param parser The parser the object will be added to.
             * @param shortName A short option name. ('x' for "-x")
             * @param longName A long option name. ("foo" for --foo)
             * @param variable How to call the variable in the usage output.
             * @param description A description of the option.
             * @param defaultValue The value to be set if not specified.
             */
            Option(
                Parser *parser,
                char shortName,
                std::string longName,
                std::string variable,
                std::string description,
                T defaultValue);

/*}}}*/
            //Option(/*{{{*/

            /**
             * @brief Create a new option.
             *
             * Construct a new option object and add it to the parser.
             *
             * @note This constructor takes no default value, so it is
             *       obligatory.
             *
             * @param parser The parser the object will be added to.
             * @param shortName A short option name. ('x' for "-x")
             * @param longName A long option name. ("foo" for --foo)
             * @param variable How to call the variable in the usage output.
             * @param description A description of the option.
             */
            Option(
                Parser *parser,
                char shortName,
                std::string longName,
                std::string variable,
                std::string description);

/*}}}*/

            //void setValue(std::string rawValue = "");/*{{{*/

            /**
             * @brief Set the value.
             *
             * @param rawValue The raw value as a string.
             */
            void setValue(std::string rawValue = "");

/*}}}*/
            //T getValue();/*{{{*/

            /**
             * @brief Get the value.
             *
             * @return The value.
             */
            T getValue();

/*}}}*/

        private:
            //void doSetValue(std::string rawValue = "");/*{{{*/

            /**
             * @brief The function doing the real work.
             *
             * @param rawValue The raw value as a string.
             */
            void doSetValue(std::string rawValue = "");

/*}}}*/

            //T _value;/*{{{*/

            /// The value.
            T _value;

/*}}}*/
    };

    template <> inline Option<bool>::Option(/*{{{*/
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

}


#endif // OPTION_OPTION_H

// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
