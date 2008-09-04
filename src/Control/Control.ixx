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

#include <string>

#include <gloox/error.h>

/*}}}*/


namespace Control
{
    inline void Control::onResourceBind(const std::string &resource)/*{{{*/
    {
#       if DEBUG
            printLog("Bind resouce: \"" + resource + "\".");
#       endif
    }/*}}}*/

    inline void Control::onResourceBindError(const gloox::Error *error)/*{{{*/
    {
#       if DEBUG
            printLog("Resource bind error.");
#       endif
    }/*}}}*/

    inline void Control::onSessionCreateError(const gloox::Error *error)/*{{{*/
    {
    }/*}}}*/

    inline void Control::onStreamEvent(gloox::StreamEvent event)/*{{{*/
    {
    }/*}}}*/
}

// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
