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


#ifndef PARAMETERPARSER_H
#define PARAMETERPARSER_H


// INCLUDE/*{{{*/


/*}}}*/


/**
 * @class ParameterParser
 * @author Dennis Felsing
 * @brief A parameter parser
 *
 * This class parses commandline parameters.
 */
class Parameter
{
    public:
        //enum Type/*{{{*/

        /**
         * @brief The type of a parameter.
         *
         * Parameters can be of general or special types. General types only
         * specify the type of the value while parameters of the special type
         * must be conform to that type.
         */
        enum Type
        {
            // General types.
            ParameterType_String,
            ParameterType_Int,
            // Special types.
            ParameterType_JID,
            ParameterType_Port
        };

/*}}}*/
        //bool addParameter(/*{{{*/

        /**
         * @brief Add an excepted parameter.
         *
         * @param name The name of the parameter, e.g. -foo or --bar.
         * @param type The type of the parameter.
         * @param isObligatory Whether the parameter must be set.
         * @return Whether the parameter was added.
         */
        bool addParameter(
            std::string name = gloox::EmptyString,
            Type type = ParameterType_String,
            bool isObligatory = false);

/*}}}*/

    private:
};


#endif // PARAMETERPARSER_H
// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
