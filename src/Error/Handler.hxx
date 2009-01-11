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


#ifndef ERROR_HANDLER_HXX
#define ERROR_HANDLER_HXX

// INCLUDES/*{{{*/

#include <libsxc/Error/Handler.hxx>
#include <libsxc/Signal/Waiter.hxx>
#include <libsxc/Signal/stopOn.hxx>

#include <File/AbcOutput.hxx>

/*}}}*/

namespace Error
{
  /**
   * This is the error handler of sxc. It implements a signal handler and an
   * error handler. Therefore it can handle signals sent to sxc and be used to
   * handle errors.
   */
  class Handler
  : public libsxc::Error::Handler
  , public libsxc::Signal::Stopper
  {
    public:
      //Handler(libsxc::Signal::Waiter &waiter, File::AbcOutput &out);/*{{{*/

      /**
       * @param waiter The signal waiter to be used when calling @ref terminate.
       * @param out The file to be used when calling @ref print.
       */
      Handler(libsxc::Signal::Waiter &waiter, File::AbcOutput &out);

/*}}}*/
      //int getExitCode();/*{{{*/

      /**
       * Get the exit code that has been assigned before using @ref terminate.
       * See @ref libsxc::Exit::Code and @ref Exit::Code for exit codes to be
       * used.
       */
      int getExitCode();

/*}}}*/
      // From Error::Handler
      //virtual void print(const std::string &message);/*{{{*/

      /**
       * Simply print a message to the account's output file. Call this method
       * in case some error occured and you want to notify the user. For
       * critical errors, see @ref printCritical.
       *
       * @param message The raw message to print; will be formatted.
       */
      virtual void print(const std::string &message);

  /*}}}*/
      //virtual void printCritical(const std::string &message);/*{{{*/

      /**
       * Print a message about an error on stderr. This method should be called
       * on errors, that are a serious threat to the correct running of the
       * program.
       *
       * @param message The message to print.
       */
      virtual void printCritical(const std::string &message);

  /*}}}*/
      //virtual void terminate(int exitCode);/*{{{*/

      /**
       * This will call the assigned @ref Signal::Waiter and make it break out
       * of the blocking running. The main function may then exit the program
       * by getting the exit code using @ref getExitCode.
       */
      virtual void terminate(int exitCode);

/*}}}*/

    private:
      int _exitCode;
      File::AbcOutput &_out;
  };
}

#endif // ERROR_HANDLER_HXX

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
