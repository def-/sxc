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

#ifndef OUTPUTDUMMY_H
#define OUTPUTDUMMY_H

// INCLUDES/*{{{*/

#include <string>
#include <File/AbcOutput.hxx>

/*}}}*/

/**
 * @class OutputDummy
 * @brief Dummy implementation of the ABC File::AbcOutput
 * @author Andreas Waidler
 *
 * Inherits from the abstract base class File::AbcOutput and definines the
 * abstract methods as "dummy" ones that do no "real" work but are optimized for
 * unit tests.
 */
class OutputDummy : public File::AbcOutput
{
    // friend class TestOutput;

    public:
        OutputDummy(const std::string &filename);
        void write(const std::string &output);

    protected:

    private:
        std::string _filename;
        std::string _createPath() const;
};

#endif // OUTPUTDUMMY_H

// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
