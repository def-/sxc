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

#ifndef FILE_IN_H
#define FILE_IN_H

namespace File
{
/** Abstract Base Class handling input (FIFOs).
 *
 * This class creates a named pipe called "in" which is placed in the directory 
 * of which the name is passed to the constructor.
 */
    class In
    {
        public:
            // File(std::string baseDir);/*{{{*/

            /** 
             */

            File(std::string baseDir);

/*}}}*/
            // ~File();/*{{{*/

            ~File();

/*}}}*/
        protected:
        private:
    };
}

#endif // FILE_IN_H
