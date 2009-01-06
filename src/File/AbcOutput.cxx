#line 2 "sxc:File/AbcOutput.cxx"
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
#include <fstream>
#include <sstream>

#include <File/AbcOutput.hxx>

#include <libsxc/Debug/Logger.hxx>

/*}}}*/

namespace File
{
  AbcOutput::AbcOutput()/*{{{*/
  : _path(NULL)
  {
  }/*}}}*/
  AbcOutput::~AbcOutput()/*{{{*/
  {
    if (isOpen())
      close();
    _dispose();
  }/*}}}*/
  void AbcOutput::initialize()/*{{{*/
  {
    _dispose();
    _path = new std::string(_createPath());
    _ofstream.exceptions(std::ofstream::badbit | std::ofstream::failbit);
  }/*}}}*/
  void AbcOutput::write(const std::string &data)/*{{{*/
  {
    _ofstream << data << std::flush;
  }/*}}}*/
  void AbcOutput::open()/*{{{*/
  {
    _ofstream.open(_path->c_str(), std::ios_base::app); // Append.
  }/*}}}*/
  void AbcOutput::close()/*{{{*/
  {
    _ofstream.close();
  }/*}}}*/
  bool AbcOutput::isOpen()/*{{{*/
  {
    return _ofstream.is_open();
  }/*}}}*/
  void AbcOutput::_dispose() throw()/*{{{*/
  {
    delete _path;
    _path = NULL;
  }/*}}}*/
  std::string AbcOutput::_indent(const std::string &prefix, std::string &text) const/*{{{*/
  {
    size_t pos = 0;
    while (true) {
      pos = text.find('\n', pos);

      std::ostringstream ss;
      ss << "Found newline (pos: " << pos << ", size: " << text.size() << ").";
      LOG(ss.str());

      if (std::string::npos == pos)
        return prefix + text;

      text.insert(pos + 1, std::string(prefix.size(), ' '));

      pos += prefix.size() + 1;
    }
  }/*}}}*/
}

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
