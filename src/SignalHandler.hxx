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



#ifndef SIGNALHANDLER_HXX
#define SIGNALHANDLER_HXX


// INCLUDE/*{{{*/

#include <sigc++/functors/slot.h>

#include <string>

/*}}}*/

/**
 * @author Dennis Felsing
 * @brief A signal handler.
 *
 * This class can be used to decide what to do on signals.
 */
class SignalHandler
{
    public:
        //typedef sigc::slot0<void> Slot;/*{{{*/

        /**
         * @brief A slot.
         *
         * Can be a class member or a function with or without arguments.
         *
         * @section Examples
         *
         * Function without arguments:
         * @code
         * sigc::ptr_fun(&myFunction);
         * @endcode
         *
         * Function with arguments:
         * @code
         * sigc::bind(sigc::ptr_fun(&myFunction), myArgument);
         * @endcode
         *
         * Class member without arguments:
         * @code
         * sigc::mem_fun(objectPtr, Class::myMethod);
         * @endcode
         *
         * Class member with arguments:
         * @code
         * sigc::bind(sigc::mem_fun(objectPtr, Class::myMethod), myArgument);
         * @endcode
         */
        typedef sigc::slot0<void> Slot;

/*}}}*/

        //static void setIgnore(unsigned int signum);/*{{{*/

        /**
         * @brief Ignore this signal.
         */
        static void setIgnore(unsigned int signum);

/*}}}*/
        //static void setDefault(unsigned int signum);/*{{{*/

        /**
         * @brief Use the default way to handle the signal.
         */
        static void setDefault(unsigned int signum);

/*}}}*/
        //static void setHandler(unsigned int signum, Slot slot);/*{{{*/

        /**
         * @brief Set your own handler for the signal.
         *
         * @param signum The signal number as defined in sys/signal.h.
         * @param slot The slot to handle the signal.
         */
        static void setHandler(unsigned int signum, Slot slot);

/*}}}*/

    private:
        //static const std::string _toString(unsigned int signum);/*{{{*/

        /**
         * @brief Convert the signum to a more meaningful text.
         *
         * @param signum The signal.
         * @return A text.
         */
        static const std::string _toString(unsigned int signum);

/*}}}*/
        //static void _check(unsigned int signum);/*{{{*/

        /**
         * @brief Check whether the signal is valid.
         *
         * Throw an exception if not.
         */
        static void _check(unsigned int signum);

/*}}}*/
        //static void _handle(int signum);/*{{{*/

        /**
         * @brief Call the assigned signal handler.
         *
         * @param signum The signal.
         */
        static void _handle(int signum);

/*}}}*/

        //static const unsigned int _limit = 32;/*{{{*/

        /// The limit of signals.
        static const unsigned int _limit = 32;

/*}}}*/
        //static Slot _handlers[_limit];/*{{{*/

        /// The assigned signal handlers.
        static Slot _handlers[_limit];

/*}}}*/
};

#endif // SIGNALHANDLER_HXX
// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
