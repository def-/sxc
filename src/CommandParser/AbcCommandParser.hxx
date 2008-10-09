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

namespace CommandParser
{
    // typedef std::pair<unsigned short, bool> param;/*{{{*/

    /**
     * @brief A parameter specification.
     *
     * Binds together the amount of mandatory parameters of a command and
     * whether the command may take a last optional parameter.
     */
    typedef std::pair<unsigned short, bool> param;

/*}}}*/
    // typedef std::pair<std::string, param> command;/*{{{*/

    /**
     * @brief A command and its parameter specification.
     *
     * Binds the command name and its parameter specification together.
     */
    typedef std::pair<std::string, param> command;

/*}}}*/
    // typedef std::map<std::string, param> commandMap;/*{{{*/

    /**
     * @brief Contains commands and their parameter specifications.
     *
     * Maps command names to their parameter specifications.
     */
    typedef std::map<std::string, param> commandMap;

/*}}}*/
    /**
     * @brief Abstract base class for command parsing.
     *
     * Child classes only have to implement the abstract method @ref
     * _createCommands(). Assumed that @ref _createCommands() returns a useable
     * @c commandMap, the parser will work out of the box.
     *
     * You might want to give derived classes a method to handle the parsed
     * command. This method could simply call @ref parse() and use the container
     * returned by @ref getParsed() to decide what to do.
     *
     * @author Andreas Waidler
     */
    class AbcCommandParser
    {
        public:
            // AbcCommandParser(const std::string &command);/*{{{*/

            /**
             * @brief Default constructor.
             *
             * Stores @a command to be parsed at a later moment.
             *
             * @param command A potential command to be parsed.
             */
            AbcCommandParser(const std::string &command);

/*}}}*/
            // virtual ~AbcCommandParser();/*{{{*/

            /// Virtual destructor, has no work to do currently.
            virtual ~AbcCommandParser();

/*}}}*/
            // void parse();/*{{{*/

            /**
             * @brief Parses the command.
             *
             * The results will be stored and can be obtained by calling @ref
             * getName(), @ref getParameterString() or @ref getParsed().
             *
             * Assumes that the command is valid and that it has not been parsed
             * yet. If any of that was a mistake an exception will be thrown.
             *
             * Internals: The command is split by seperating the parameters by
             * a space (' '). The parameter list will be sliced until the amount
             * of mandatory parameters minus one is reached. If the command is
             * overloadable this method tries to slice the remaining part of the
             * list again. Everything remaining in the parameter list is now
             * considered to be the last parameter, thus ignoring any
             * whitespaces in it.
             *
             * @exception InputException(InvalidUsage) If already parsed.
             * @exception InputException(NoCommand) When command prefix not
             *            found.
             * @exception InputException(InvalidCommand) When the command does
             *            not match any specifications returned by
             *            @ref _createCommands().
             * @see getParsed() For information how to use the parsed command.
             */
            void parse();

/*}}}*/
            // const std::string &get() const;/*{{{*/

            /**
             * @brief Returns a constant reference of the command.
             * @return Constant reference of the command that has been passed to
             *         the constructor.
             */
            const std::string &get() const;

/*}}}*/
            // const std::string &getName() const;/*{{{*/

            /**
             * @brief Returns a reference of the name of the command.
             * @exception InputException(InvalidUsage) If not parsed.
             * @return Reference of the name of the command.
             */
            const std::string &getName() const;

/*}}}*/
            // const std::string &getParameterString() const;/*{{{*/

            /**
             * @brief Returns a constant reference to all parameters
             * @exception InputException(InvalidUsage) If not parsed.
             * @return Constant reference to a string containing all parameters.
             */
            const std::string &getParameterString() const;

/*}}}*/
            // const std::deque<std::string> &getParsed() const;/*{{{*/

            /**
             * @brief Returns a constant container with the parsed command.
             *
             * The container returned will contain the name of the command as
             * first element (@ref getName()). The following elements will be
             * the contents of the parameter list (@ref getParameterString()),
             * seperated by a space (' ') until the number of arguments is
             * reached. The last element will contain everything from the
             * beginning of the last parameter to the end of the parameter list,
             * thus ignoring any whitespaces. If the command is specified as
             * overloadable and the "last parameter" contains an additional
             * space, it will be sliced again.
             *
             * @return Constant double-ended queue containing strings, each
             *         having the value of a space-seperated part of the command
             */
            const std::deque<std::string> &getParsed() const;

/*}}}*/

        protected:
            // const commandMap &_getCommands() const;/*{{{*/

            /**
             * @brief Returns a constant reference to all valid commands.
             *
             * If the @c commandMap @ref _commands has not been set (i.e. it is
             * empty) the abstract method @ref _createCommands() is called and
             * the resulting @c commandMap is stored in @ref _commands. This
             * method then returns a constant reference to it.
             *
             * @return Constant reference to the result of @ref _createCommands()
             */
            const commandMap &_getCommands() const;

/*}}}*/
            // static const char _commandPrefix = ':';/*{{{*/

            /// Prefix for all commands.
            static const char _commandPrefix = ':';

/*}}}*/

        private:
            // virtual commandMap _createCommands() const = 0;/*{{{*/

            /**
             * @brief Creates a container holding all possible commands.
             *
             * @note Pure virtual, aka abstract.
             *
             * @return All valid commands and the specification of their
             *         parameters
             */
            virtual commandMap _createCommands() const = 0;

/*}}}*/
            // static commandMap _commands;/*{{{*/

            /**
             * @brief Holds all valid commands.
             * Will be set by the abstract method @ref _createCommands().
             * @warning Never access directly, use @ref _getCommands().
             */
            static commandMap _commands;

/*}}}*/
            // std::string _command;/*{{{*/

            /// The command to parse which has been passed to the constructor.
            std::string _command;

/*}}}*/
            // std::string _commandName;/*{{{*/

            /// The name of the command, will be set by @ref parse().
            std::string _commandName;

/*}}}*/
            // std::string _parameters;/*{{{*/

            /// The parameter list of the command, set by @ref parse()
            std::string _parameters;

/*}}}*/
            // std::deque<std::string> _parsed;/*{{{*/

            /// Results of @ref parse(), see that docblock for information.
            std::deque<std::string> _parsed;

/*}}}*/
            // bool _isParsed;/*{{{*/

            /// Indicates whether @ref parse() did return successfully.
            bool _isParsed;

/*}}}*/
    };
}

#endif // COMMANDPARSER_ABCCOMMANDPARSER_HXX

// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
