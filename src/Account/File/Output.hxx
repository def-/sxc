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

#ifndef ACCOUNT_FILE_OUTPUT_HXX
#define ACCOUNT_FILE_OUTPUT_HXX

// INCLUDES/*{{{*/

#include <string>
#include <File/AbcOutput.hxx>

/*}}}*/

namespace Account
{
  namespace File
  {
    /**
     * @brief Main output class for sxc.
     *
     * Creates the file $JID/out which displays messages from sxc and from
     * the server.
     *
     */
    class Output : public ::File::AbcOutput
    {
      public:
        // Output(const std::string &accountJid);/*{{{*/

        /**
         * @brief Initializes the object.
         *
         * @param accountJid The JID of this local account.
         */
        Output(const std::string &accountJid);

/*}}}*/
        ~Output();

        virtual void write(const std::string &message);

      protected:


      private:
        const std::string _accountJid;
        // std::string _createPath() const;/*{{{*/

        /**
         * @brief Creates a string containing the path of this file.
         *
         * @see File::AbcOutput::_createPath()
         *
         * @return $accountName/out
         */
        std::string _createPath() const;

/*}}}*/
        // std::string _format(const std::string &output) const;/*{{{*/

        /**
         * @brief Formats the output.
         *
         * @param output String to be formatted.
         * @return A formatted string.
         */
        std::string _format(const std::string &output) const;

/*}}}*/
    };
  }
}

#endif // ACCOUNT_FILE_OUTPUT_HXX

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
