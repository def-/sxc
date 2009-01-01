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

//#include <File/AbcOutput.hxx>

/*}}}*/

namespace Error
{
  class Handler
  : public libsxc::Error2::Handler
  , public libsxc::Signal::Stopper
  {
    public:
      //Handler(libsxc::Signal::Waiter &waiter);/*{{{*/

      /**
       */
      Handler(libsxc::Signal::Waiter &waiter /*, File::AbcOutput &out*/);

/*}}}*/
      //int getExitCode();/*{{{*/

      /**
       */
      int getExitCode();

/*}}}*/
      // From Error::Handler
      //void print(const std::string &message);/*{{{*/

      /**
       */
      void print(const std::string &message);

  /*}}}*/
      //void printCritical(const std::string &message);/*{{{*/

      /**
       */
      void printCritical(const std::string &message);

  /*}}}*/
      //void terminate(int exitCode);/*{{{*/

      /**
       */
      void terminate(int exitCode);

/*}}}*/

    private:
      int _exitCode;
      //File::AbcOutput &_out;
  };
}

#endif // ERROR_HANDLER_HXX

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
