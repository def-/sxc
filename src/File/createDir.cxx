#line 2 "sxc:File/createDir.cxx"
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

// INCLUDES/*{{{*/

#ifdef HAVE_CONFIG_H
# include <config.hxx>
#endif

#include <string>
#include <cerrno>
#include <sys/stat.h>

#include <libsxc/Debug/Logger.hxx>

#include <File/Exception/errnoToException.hxx>
#include <File/Exception/BadFile.hxx>

/*}}}*/

namespace File
{
  void createDir(const std::string &path)
  {
    // We first try to get the file stats, to see whether this file, if
    // existing, is a directory.
    struct stat fstat;
    if (0 == stat(path.c_str(), &fstat)) {
      LOG("File already exists: \"" + path + "\"");
      // Is it a directory?
      if (!S_ISDIR(fstat.st_mode)) {
        throw Exception::BadFile(("Not a directory: " + path).c_str());
      }
      // It is a directory, so there is no need to do anything.
      LOG("Directory already exists: \"" + path + "\"");
      return;
    }

    if (ENOENT != errno) {
      throw Exception::errnoToException(
        errno,
        ("Could not get fstat: " + path).c_str());
    }

    LOG("Create directory: \"" + path + "\"");

    // Directory does not exist. Create it with chmod 700.
    if (0 == mkdir(path.c_str(), S_IRUSR | S_IWUSR | S_IXUSR))
      return;

    throw Exception::errnoToException(
      errno,
      ("Could not create directory: " + path).c_str());
  }
}

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
