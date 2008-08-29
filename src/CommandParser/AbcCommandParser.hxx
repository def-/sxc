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

#ifndef COMMANDPARSER_ABCCOMMANDPARSER_HXX
#define COMMANDPARSER_ABCCOMMANDPARSER_HXX

// INCLUDES/*{{{*/

#include <string>
#include <deque>
#include <map>

/*}}}*/

/**
 * @brief DATA LOSS ZOMFGOLOLOL
 * @author Andreas Waidler
 *
 */
namespace CommandParser
{
    typedef std::pair<unsigned short, bool> param;
    typedef std::pair<std::string, param> command;
    typedef std::map<std::string, param> commandMap;

    class AbcCommandParser
    {
        public:
            AbcCommandParser(const std::string &command);
            virtual ~AbcCommandParser();
            void parse();
            const std::string &get() const;
            const std::string &getName() const;
            const std::string &getParameterString() const;
            const std::deque<std::string> &getParsed() const;

        protected:
            const commandMap &_getCommands() const;
            static const char _commandPrefix = ':';

        private:
            virtual commandMap _createCommands() const = 0;

            /// Never access directly!
            static commandMap _commands;

            const std::string &_command;
            std::string _commandName;
            std::string _parameters;
            std::deque<std::string> _parsed;
            bool _isParsed;
    };
}

#endif // COMMANDPARSER_ABCCOMMANDPARSER_HXX

// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
