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


#ifndef EXCEPTION_GLOOXEXCEPTION_HXX
#define EXCEPTION_GLOOXEXCEPTION_HXX


// INCLUDE/*{{{*/

#include <string>

#include <libsxc/Exception/Exception.hxx>

/*}}}*/

namespace libsxc
{
    namespace Exception
    {
        /**
         * @author Dennis Felsing
         * @brief An exception class for gloox errors.
         */
        class GlooxException : public Exception
        {
            public:
                //GlooxException(Type type, std::string message);/*{{{*/

                /**
                 * @brief Create a gloox exception object.
                 *
                 * @param type The type of the exception.
                 * @param message A text describing the exception more verbose.
                 */
                GlooxException(Type type, std::string message);

    /*}}}*/
                //void createDescription() throw();/*{{{*/

                /**
                 * @brief Create the description text.
                 */
                void createDescription() throw();

    /*}}}*/
        };
    }
}

#endif // EXCEPTION_GLOOXEXCEPTION_HXX
// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
