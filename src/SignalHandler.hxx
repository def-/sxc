// LICENSE/*{{{*/
/*
  sxc - Simple Xmpp Client
  Copyright (C) 2008 Dennis Felsing, Andreas Waidler

  Permission to use, copy, modify, and/or distribute this software for any
  purpose with or without fee is hereby granted, provided that the above
  copyright notice and this permission notice appear in all copies.

  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
/*}}}*/



#ifndef SIGNALHANDLER_HXX
#define SIGNALHANDLER_HXX


// INCLUDE/*{{{*/

#include <sigc++/functors/slot.h>

#include <string>

/*}}}*/

/**
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
