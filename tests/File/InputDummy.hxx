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

#ifndef INPUTDUMMY_H
#define INPUTDUMMY_H

// INCLUDES/*{{{*/

#include <string>
#include <File/AbcInput.hxx>

/*}}}*/

/**
 * @class InputDummy
 * @brief Dummy implementation of the ABC File::AbcInput
 * @author Andreas Waidler
 *
 * Inherits from the abstract base class File::AbcInput and definines the
 * abstract methods as "dummy" ones that do no "real" work but are optimized for
 * unit tests.
 */
class InputDummy : public File::AbcInput
{
    friend class TestInput;

    public:
        InputDummy(const std::string &filename);
        const std::string &getLastInput() const;

    protected:

    private:
        std::string _filename;
        std::string _lastInput;
        std::string _createPath() const;
        void _handleInput(const std::string&);
};

#endif // INPUTDUMMY_H

// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
