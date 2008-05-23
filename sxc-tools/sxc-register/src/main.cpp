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

#include <gloox/jid.h>
#include <gloox/client.h>

#include "Registrator.h"
#include "Error.h"

/*}}}*/

/**
 * @file main.cpp
 * @author Dennis Felsing
 * @brief The starting point of sxc-register.
 *
 * Create a JID object from the parameter and start the registration process by
 * running @ref Registrator.
 */

int main(int argc, char *argv[])
{
    if (argc != 2)
        return ErrorParametersInvalid;

    gloox::JID jid(argv[1]);

    if (jid.username().empty())
        return ErrorJidInvalid;

    Registrator registrator;
    registrator.start(jid);
}
