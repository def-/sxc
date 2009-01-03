// LICENSE/*{{{*/
/*
  sxc - Simple Xmpp Client
  Copyright (C) 2008 Dennis Felsing, Andreas Waidler

  Permission to use, copy, modify, and/or distribute this software for any
  purpose with or without fee is hereby granted, provided that the above
  copyright notice and this permission notice appear in all copies.

  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
/*}}}*/

#ifndef CONTACT_COMMAND_COMMAND_HXX
#define CONTACT_COMMAND_COMMAND_HXX

// INCLUDES/*{{{*/

#include <string>

#include <CommandParser/AbcCommandParser.hxx>
#include <Account/Account.hxx>
#include <Contact/Contact.hxx>

/*}}}*/

namespace Contact
{
  /**
   * @brief Parses and executes commands for the contacts.
   *
   */
  class Command : CommandParser::AbcCommandParser
  {
    public:
      // Command(Contact &, const std::string &);/*{{{*/

      /**
       * @brief Default constructor.
       *
       * For the purpose of the Account and Contact objects see @ref
       * execute().
       *
       * @param contact The contact object which received this command.
       * @param command A command to be parsed.
       */
      Command(
        Contact &contact,
        const std::string &command);

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

    protected:

    private:
      //Contact &_contact;/*{{{*/

      /// The contact object.
      Contact &_contact;

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

#endif // CONTACT_COMMAND_COMMAND_HXX

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
