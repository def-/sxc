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

// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
