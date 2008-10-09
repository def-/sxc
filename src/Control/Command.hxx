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
#include <Control/Control.hxx>

/*}}}*/

namespace Control
{
    class Command : CommandParser::AbcCommandParser
    {
        public:
            // Command(Control &control, const std::string &command);/*{{{*/

            /**
             * @brief Default constructor, initializes the object.
             *
             * Calls parent constructor and sets passed properties.
             *
             * @param control The control object to use to execute commands.
             * @param command A command to be parsed.
             */
            Command(Control &control, const std::string &command);

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
             * @exception std::exception This should usually not happen.
             */
            void execute();

/*}}}*/

        private:
            //Control &_control;/*{{{*/
            /// The control object.
            Control &_control;

/*}}}*/
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

#endif // CONTROL_COMMAND_COMMAND_HXX

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
