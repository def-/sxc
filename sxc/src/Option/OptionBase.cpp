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

/* $Id$ */

// INCLUDE/*{{{*/

#include "OptionBase.h"

/*}}}*/

namespace Option
{
    OptionBase::OptionBase(/*{{{*/
        char shortName,
        std::string longName,
        std::string variable,
        std::string description,
        bool requiresArgument,
        bool isObligatory)
    : _shortName(shortName),
      _longName(longName),
      _variable(variable),
      _description(description),
      _requiresArgument(requiresArgument),
      _isObligatory(isObligatory),
      _isSet(false)
    {
    }/*}}}*/

    void OptionBase::setValue(std::string rawValue)/*{{{*/
    {
        std::cout << "Wrong one, FUCK!" << std::endl;
    }/*}}}*/

    char OptionBase::getShortName()/*{{{*/
    {
        return _shortName;
    }/*}}}*/

    std::string OptionBase::getLongName()/*{{{*/
    {
        return _longName;
    }/*}}}*/

    std::string OptionBase::getName()
    {
        if ("" != _longName)
            return _longName;
        else if (' ' != _shortName)
            return "" + _shortName;
        return "";
    }

    std::string OptionBase::getVariable()/*{{{*/
    {
        return _variable;
    }/*}}}*/

    std::string OptionBase::getDescription()/*{{{*/
    {
        return _description;
    }/*}}}*/

    bool OptionBase::getRequiresArgument()/*{{{*/
    {
        return _requiresArgument;
    }/*}}}*/

    bool OptionBase::getIsObligatory()/*{{{*/
    {
        return _isObligatory;
    }/*}}}*/

    bool OptionBase::getIsSet()/*{{{*/
    {
        return _isSet;
    }/*}}}*/
}

// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
