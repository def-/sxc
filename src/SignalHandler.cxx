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


// INCLUDE/*{{{*/

#include <stdexcept>
#include <sstream>

#include <sys/signal.h>
#include <sigc++/sigc++.h>

#include <SignalHandler.hxx>
#include <print.hxx>

#ifdef HAVE_CONFIG_H
#   include <config.hxx>
#endif

/*}}}*/

SignalHandler::Slot SignalHandler::_handlers[_limit];

void SignalHandler::setIgnore(unsigned int signum)/*{{{*/
{
    SignalHandler::_check(signum);

#   ifdef DEBUG
        std::stringstream ss;
        ss << "Setting signal to be ignored: " << signum << " ("
           << SignalHandler::_toString(signum) << ").";
        printErr(ss.str());
#   endif

    signal(signum, SIG_IGN);
    SignalHandler::_handlers[signum].disconnect();
}/*}}}*/
void SignalHandler::setDefault(unsigned int signum)/*{{{*/
{
    SignalHandler::_check(signum);

#   ifdef DEBUG
        std::stringstream ss;
        ss << "Setting signal to be handled as default: " << signum << " ("
           << SignalHandler::_toString(signum) << ").";
        printErr(ss.str());
#   endif

    signal(signum, SIG_DFL);
    SignalHandler::_handlers[signum].disconnect();
}/*}}}*/
void SignalHandler::setHandler(unsigned int signum, Slot slot)/*{{{*/
{
    SignalHandler::_check(signum);

#   ifdef DEBUG
        std::stringstream ss;
        ss << "Setting signal to be handled in a custom way: " << signum << " ("
           << SignalHandler::_toString(signum) << ").";
        printErr(ss.str());
#   endif

    SignalHandler::_handlers[signum] = slot;
    signal(signum, &SignalHandler::_handle);
}/*}}}*/

const std::string SignalHandler::_toString(unsigned int signum)/*{{{*/
{
    switch (signum) {
    case SIGHUP:
        return "SIGHUP (hangup detected)";
    case SIGINT:
        return "SIGINT (interrupt from keyboard)";
    case SIGQUIT:
        return "SIGQUIT (quit signal)";
    case SIGILL:
        return "SIGILL (illegal instruction)";
    case SIGABRT:
        return "SIGABRT (abort signal)";
    case SIGFPE:
        return "SIGFPE (floating point exception)";
    case SIGKILL:
        return "SIGKILL (kill signal)";
    case SIGSEGV:
        return "SIGSEGV (segmentation fault)";
    case SIGPIPE:
        return "SIGPIPE (broken pipe)";
    case SIGALRM:
        return "SIGALRN (timer signal)";
    case SIGTERM:
        return "SIGTERM (termination signal)";
    case SIGBUS:
        return "SIGBUS (bus error)";
    default:
        return "Unknown";
    }
}/*}}}*/
void SignalHandler::_check(unsigned int signum)/*{{{*/
{
    if (SignalHandler::_limit < signum) {
        std::stringstream ss;
        ss << "Invalid signal value: " << signum;
        throw std::logic_error(ss.str());
    }
}/*}}}*/
void SignalHandler::_handle(int signum)/*{{{*/
{
#   ifdef DEBUG
        std::stringstream ss;
        ss << "Signal received: " << signum << " ("
           << SignalHandler::_toString(signum) << ").";
        printErr(ss.str());
#   endif

    SignalHandler::_handlers[signum]();
}/*}}}*/

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
