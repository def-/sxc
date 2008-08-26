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


#ifndef OPTION_OPTIONPORT_HXX
#define OPTION_OPTIONPORT_HXX


// INCLUDE/*{{{*/

#include <Option/Option.hxx>

/*}}}*/

namespace Option
{
    /**
     * @author Dennis Felsing
     * @brief A class representing an option for a port.
     *
     * This class checks whether the value is a valid port.
     */
    class OptionPort : public Option<int>
    {
        public:
            //OptionPort(parser, short, long, variable, description);/*{{{*/

            /**
             * @brief Create a new port option.
             *
             * Construct a new port option object and add it to the parser.
             *
             * @param parser The parser the object will be added to.
             * @param shortName A short option name. ('x' for "-x")
             * @param longName A long option name. ("foo" for --foo)
             * @param variable How to call the variable in the usage output.
             * @param description A description of the option.
             */
            OptionPort(
                Parser *parser,
                char shortName,
                std::string longName,
                std::string variable,
                std::string description);

/*}}}*/

            //void setValue(std::string rawValue);/*{{{*/

            /**
             * @brief Set the value.
             *
             * Set the port to the string given and check whether it is valid.
             *
             * @param rawValue The raw value as a string.
             */
            void setValue(std::string rawValue);

/*}}}*/
    };
}


#endif // OPTION_OPTIONPORT_HXX
// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
