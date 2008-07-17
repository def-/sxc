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


#ifndef OPTION_PARSE_H
#define OPTION_PARSE_H


// INCLUDE/*{{{*/

#include <string>
#include <vector>

#include "OptionBase.h"

/*}}}*/

namespace Option
{
    /**
     * @class Parser
     * @author Dennis Felsing
     * @brief An option parser
     *
     * This class parses program options.
     */
    class Parser
    {
        public:
            //void addOption(OptionBase *option);/*{{{*/

            /**
             * @brief Add an option to be parsed.
             *
             * @param option The option.
             */
            void addOption(OptionBase *option);

/*}}}*/
            //void parse(const char *argv[]);/*{{{*/

            /**
             * @brief Parse all options.
             *
             * Parse all options that have been added before using @ref
             * addOption(). Errors get thrown.
             *
             * @param argv The raw arguments.
             */
            void parse(char *argv[]);

/*}}}*/
            //void showUsage();/*{{{*/

            /**
             * @brief Show the usage.
             *
             * Output to stderr how to use the program.
             */
            void showUsage();

/*}}}*/

        private:
            std::string getUsageShort(OptionBase option);
            std::string getUsageLine(OptionBase option);

            //std::vector<OptionBase *> _options;/*{{{*/

            /// The normal options.
            std::vector<OptionBase *> _options;

/*}}}*/
            //std::vector<OptionBase *> _namelessOptions;/*{{{*/

            /// The options that are not introduced by a "-x" or "--foo".
            std::vector<OptionBase *> _namelessOptions;

/*}}}*/
            //std::string _programName;/*{{{*/

            /// The name of the program.
            std::string _programName;

/*}}}*/
    };
}


#endif // OPTION_PARSE_H
// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
