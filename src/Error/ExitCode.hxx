// LICENSE/*{{{*/
/*
  sxc - Simple Xmpp Client
  Copyright(C) 2008 Dennis Felsing, Andreas Waidler

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


#ifndef ERROR_EXITCODE_HXX
#define ERROR_EXITCODE_HXX


// INCLUDE/*{{{*/


/*}}}*/

namespace Error
{
  /**
   * A central point to define exit codes of sxc, so every code has only one
   * meaning.
   */
  enum ExitCode
  { NoError = 0 // No problem occured.
  , General = 64
  // Program option errors./*{{{*/
  , OptionNotSet = 80
  , OptionSetMultiple = 81
  , OptionUnknown = 82
  , ValueNotSet = 83
  , PortInvalid = 84
  , JidInvalid = 85
  , ValueInvalid = 86
  , OptionsConflicting = 87
/*}}}*/
  // Gloox errors./*{{{*/
  , Connection = 90
  , Registration = 91
  , PrivacyList = 92
  , SessionCreate = 93
  , Stanza = 94
  , Stream = 95
/*}}}*/
  // File errors./*{{{*/
  // TODO
  , FileMissing    = 150
  , FileExists     /* = @ */
  , FileLocked     /* = @ */
  , BadPath        /* = @ */
  , BadFile        /* = @ */
  , AccessDenied   /* = @ */
  , OpenFailed     /* = @ */
  , WriteFailed    /* = @ */
  , ReadFailed     /* = @ */
  , CloseFailed    /* = @ */
  , NoCommand      /* = @ */
  , InvalidCommand /* = @ */
/*}}}*/
  // Generic errors:
  , InvalidUsage = 200
/*}}}*/
  };
}


#endif // ERROR_EXITCODE_HXX
// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
