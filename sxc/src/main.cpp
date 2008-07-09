// TODO:
// - more consts and references (speed)
// - comparisons with (const == var)
// - remove compiler warnings (-Wall -Wextra)
// - add test to the building system
// - write some more tests
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
#include <sstream>
#include <gloox/jid.h>

#include "Option/Parser.h"
#include "Option/Option.h"
#include "Option/OptionPort.h"
#include "Control/Control.h"
#include "Exception/Exception.h"

/*}}}*/

/**
 * @file main.cpp
 * @author Dennis Felsing
 * @brief The starting point of sxc.
 *
 * Parse the parameters the program was started with and then initialize the
 * @ref Control::Control.
 */

int main(int argc, char *argv[])/*{{{*/
{
    Option::Parser parser;
    Option::OptionPort port(
        &parser, 'p', "port", "port", "0 - 65535, -1 for default");
    Option::Option<gloox::JID> jid(
        &parser, ' ', "", "jid", "user@domain[/resource]");

    try {
        parser.parse(argv);
    } catch (Exception::Exception &e) {
        std::cout << e.getDescription() << std::endl;
        parser.showUsage();
        return e.getType();
    }

    try {
        Control::Control::getInstance().initialize(
            jid.getValue(), port.getValue());
        pause(); // Run forever (until a signal is received).
    } catch (Exception::Exception &e) {
        Control::Control::getInstance().handleError(e, true);
    }

    return 0;
}/*}}}*/
// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
