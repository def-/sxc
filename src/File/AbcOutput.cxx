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
#   include <config.hxx>
#   include <print.hxx>
#endif

#include <string>
#include <fstream>

#include <File/AbcOutput.hxx>

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
        _ofstream.open(_path->c_str());
    }/*}}}*/
    void AbcOutput::close()/*{{{*/
    {
        _ofstream.close();
    }/*}}}*/
    bool AbcOutput::isOpen() const/*{{{*/
    {
        return _ofstream.is_open();
    }/*}}}*/
    void AbcOutput::_dispose() throw()/*{{{*/
    {
        delete _path;
        _path = NULL;
    }/*}}}*/
}

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
