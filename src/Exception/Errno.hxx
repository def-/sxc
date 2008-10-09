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

/**
 * @file Errno.hxx
 * @author Andreas Waidler
 * @brief Contains functions for handling the system errno variable.
 */

#ifndef EXCEPTION_ERRNO_HXX
#define EXCEPTION_ERRNO_HXX

// INCLUDES/*{{{*/

#include <libsxc/Exception/Type.hxx>

/*}}}*/


namespace Exception
{

    /** Transforms the passed errno into an exception type.
     *
     * For a list of possible errno's and their meaning, look at the following
     * man pages:
     * @li man 2 stat
     * @li man 3 mkfifo
     *
     * @param p_errno The errno that occured and that should be transformed.
     * @return An Exception::Type that matches the passed errno.
     */
    libsxc::Exception::Type errnoToType(int p_errno);
}

#endif // EXCEPTION_ERRNO_HXX

// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker

