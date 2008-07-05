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


#ifndef EXCEPTION_TYPE_H
#define EXCEPTION_TYPE_H


// INCLUDE/*{{{*/

/*}}}*/

/**
 * @file Exception
 * @author Dennis Felsing
 * @brief An enum for all exception types and their exit codes.
 */

namespace Exception
{
    //enum Type/*{{{*/

    /// Exception types and return codes.
    enum Type
    {
        General = 64,
        // Program argument exceptions./*{{{*/
        ArgumentNotSet = 80,
        ArgumentUnknown = 81,
        ValueUnspecified = 82,
        PortInvalid = 83,
        JidInvalid = 84,
/*}}}*/
        // File errors./*{{{*/
        // TODO
/*}}}*/
        // Gloox errors./*{{{*/
        // TODO
/*}}}*/
    };
/*}}}*/
}


#endif // EXCEPTION_TYPE_H
// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
