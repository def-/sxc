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
    {
    }

/*}}}*/
    AbcOutput::~AbcOutput()/*{{{*/
    {
        if (isOpen())
            close();
    }

/*}}}*/
    void AbcOutput::initialize()/*{{{*/
    {
        _path = _createPath();
        _file.exceptions(std::ofstream::badbit | std::ofstream::failbit);
    }

/*}}}*/
    void AbcOutput::write(std::string text)/*{{{*/
    {
        _file << _format(text) << std::flush;
    }

/*}}}*/
    void AbcOutput::open()/*{{{*/
    {
        _file.open(_path.c_str());
    }

/*}}}*/
    void AbcOutput::close()/*{{{*/
    {
        _file.close();
    }

/*}}}*/
    bool AbcOutput::isOpen()/*{{{*/
    {
        return _file.is_open();
    }

/*}}}*/
}

// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
