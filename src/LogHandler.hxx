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



#ifndef CONTROL_LOGHANDLER_HXX
#define CONTROL_LOGHANDLER_HXX


// INCLUDE/*{{{*/

#include <string>

#include <gloox/gloox.h>
#include <gloox/loghandler.h>

/*}}}*/

/**
 * @brief Handle debug messages between gloox and the server.
 */
class LogHandler : public gloox::LogHandler
{
    //void handleLog(LogLevel level, LogArea area, const string &msg);/*{{{*/

    /**
     */
    void handleLog(
        gloox::LogLevel level,
        gloox::LogArea area,
        const std::string &message);

/*}}}*/
};

#endif // CONTROL_LOGHANDLER_HXX
// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
