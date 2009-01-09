// LICENSE/*{{{*/
/*
  libsxc
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

#ifndef FILE_ABCINFO_HXX
#define FILE_ABCINFO_HXX

// INCLUDE/*{{{*/

#include <string>

/*}}}*/

namespace File
{
  /**
   */
  class AbcInfo
  {
    public:
      virtual ~AbcInfo() {}

      //virtual void initialize();/*{{{*/

      /**
       * Create the nfo-directory if not existing. This method will also
       * initialize the @ref _path variable by calling @ref _createPath.
       */
      virtual void initialize();

/*}}}*/
      //virtual void remove();/*{{{*/

      /**
       * Delete the nfo-directory, if existing and empty. In derived classes
       * reimplement, use @ref removeFile on the files you are using and then
       * call this method, which will only delete the directory if no files
       * were added to the directory outside of sxc.
       */
      virtual void remove();

/*}}}*/

    protected:
      //template <typename T> void _set(const string &key, T &value);/*{{{*/

      /**
       * A generic setting method to be used for additional files in derived
       * classes. Any current content is discarded.
       */
      template <typename T> void _set(const std::string &key, T &value);

/*}}}*/
      //virtual void _removeFile(const std::string &key);/*{{{*/

      /**
       * Remove a file. Should be used in derived classes in their
       * implementation of the @ref remove method to get rid of the created
       * files.
       */
      virtual void _removeFile(const std::string &key);

/*}}}*/

      //virtual const std::string _createPath() = 0;/*{{{*/

      /**
       * This method has to return a valid path for the info-directory of this
       * object. It should be relative to the current directory (not starting
       * with a slash) and must end with a slash (/).
       */
      virtual const std::string _createPath() = 0;

/*}}}*/

    private:
      std::string _path;
  };
}

#include <File/AbcInfo.ixx>

#endif // FILE_ABCINFO_HXX
// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
