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

#ifndef CONTROL_COMMAND_COMMAND_HXX
#define CONTROL_COMMAND_COMMAND_HXX

// INCLUDES/*{{{*/

#include <string>

#include <CommandParser/AbcCommandParser.hxx>

/*}}}*/

namespace Control
{
    namespace Command
    {
        class Command : CommandParser::AbcCommandParser
        {
            public:
                // Command(const std::string &command);/*{{{*/

                /**
                 * @brief Default constructor, calls parent constructor.
                 *
                 * @param command A command to be parsed.
                 */
                Command(const std::string &command);

/*}}}*/
                // ~Command();/*{{{*/

                /// Destructor, has nothing to do currently.
                ~Command();

/*}}}*/
                // void execute();/*{{{*/

                /**
                 * @brief Executes the passed command.
                 *
                 * Calls @ref parse() and @ref getParsed(). Some parameters may
                 * be checked by this method. Usually the parameters are passed
                 * on without being checked. The associated method will be
                 * called and may throw an exception.
                 *
                 * @note Exception handling has to be done by the caller.
                 *
                 * @exception InputException(InvalidCommand) A check failed.
                 * @exception libsxc::Exception::Exception Childs of this basic
                 *            exception may be thrown by invoked methods.
                 * @exception std::out_of_range Accessing an element of returned
                 *            by @ref getParsed() that does not exist. This
                 *            would be a bug in this class (or its parent).
                 * @exception std::exception This should usually not happen.
                 */
                void execute();

/*}}}*/

            protected:

            private:
                // commandMap _createCommands() const;/*{{{*/

                /**
                 * @brief Creates a container holding all possible commands.
                 *
                 * @return All valid commands and the specification of their
                 *         parameters.
                 */
                CommandParser::commandMap _createCommands() const;

/*}}}*/
        };
    }
}

#endif // CONTROL_COMMAND_COMMAND_HXX

// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker