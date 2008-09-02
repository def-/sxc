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

#ifndef FILE_ABCINPUT_HXX
#define FILE_ABCINPUT_HXX

// INCLUDES/*{{{*/

#include <string>
#include <fstream>
#include <pthread.h>

/*}}}*/

namespace File
{
    /**
     * @author Andreas Waidler
     * @brief Abstract Base Class handling input (FIFOs).
     *
     * Handles creation and checking of, listening (non-blocking) on and reading
     * (blocking) off FIFOs. Contains pure virtual methods that will define the
     * location of the FIFO and how the input is handled.
     */
    class AbcInput
    {
        public:
            // AbcInput();/*{{{*/

            /// Constructor, initializes private variables with default values.
            AbcInput();

/*}}}*/
            // virtual ~AbcInput();/*{{{*/

            /// Closes FIFO and subthread if open/running.
            virtual ~AbcInput();

/*}}}*/
            // void initialize(bool notPhysical=false);/*{{{*/

            /**
             * @brief Does a more high-level initialization of the object.
             *
             * Apart from the constructor which does only a low-level
             * initialization, this method does a more high-level one, including
             * calls to abstract methods which cannot be called in the
             * constructor.
             *
             * Calls @ref _createPath() to set @ref _path. Tries to create 
             * the FIFO or checks its permissions by calling @ref _tryCreate() 
             * or @ref _validate().
             *
             * @note This method has to be called before any other method can be
             *       used. You may want to call it in the constructor of child
             *       classes.
             *
             * @param notPhysical Disable validation or creation of the physical
             *        file, just initialize this object.
             */
            void initialize(bool notPhysical=false);

/*}}}*/
            // void listen(bool blocking=false);/*{{{*/

            /**
             * @brief Initiates listening on the FIFO.
             *
             * If @a blocking is set to @c true this method will read blocking,
             * i.e. it will finish when @ref close() is run. Per default, @a 
             * blocking is @c false.
             *
             * This method creates a thread that executes @ref _listen()
             * which will run in the background. If @a blocking is true @c
             * pthread_join() is called which causes this method to wait until
             * the thread terminates.
             *
             * @param blocking Whether to listen blocking or non-blocking.
             */
            void listen(bool blocking = false);

/*}}}*/
            // void close();/*{{{*/

            /**
             * @brief Closes the FIFO physically, terminates @ref listen();
             *
             * Sets a flag and opens and closes the FIFO. Then, @c
             * pthread_join() will be called to enter the thread which listens
             * on it.
             *
             * That thread does always check the flag and terminate cleanly if
             * it is set. @c close() has to open and close the FIFO
             * because the method open() of the FIFO blocks until the other end
             * opens and closes the pipe.
             *
             * The thread should terminate very quickly after @c close() has
             * been called, which makes @c pthread_join() return. Then, @c
             * close() does some cleanups.
             */
            void close();

/*}}}*/

        protected:
            // void _create();/*{{{*/

            /**
             * @brief Creates the FIFO physically.
             *
             * @exception FileInputException If mkfifo() fails. @c
             *            Exception::Type is set to @ref
             *            Exception::errnoToType().
             */
            void _create();

/*}}}*/
            // void _validate();/*{{{*/

            /**
             * @brief Checks whether FIFO is valid.
             *
             * "Valid" means:
             * @li file owner uid == sxc uid
             * @li readable and writable for only the owner
             *
             * If any of this assertions fails, the FIFO is invalid. Normally,
             * the FIFO should exist and be valid, except sxc has not been run
             * before (in this directory) or someone tampered with the directory
             * structure.
             *
             * @c Exception::Type is set to the appropriate error, so
             * a Exception::FileMissing can be caught, and the FIFO can be
             * created by calling @ref _create().
             *
             * @exception Exception::FileInputException When file is invalid.
             */

            void _validate();

/*}}}*/
            // void _read();/*{{{*/

            /**
             * @brief Reads blocking from the FIFO.
             *
             * Stops reading when the other end closes the pipe. Then, all input
             * will be passed to @ref _handleInput().
             *
             * Before calling @ref _handleInput(), @ref _mustClose will be
             * checked. This method will return if it is true.
             *
             * @note The only way to stop this method is to "unblock" the call
             *       to open(). This can be done by opening and closing the
             *       other end of the named pipe.
             */
            void _read();

/*}}}*/

        private:
            // std::string _path;/*{{{*/

            /// The path including file name where the FIFO is located.
            std::string _path;

/*}}}*/
            // std::ifstream _fifo;/*{{{*/

            /// The FIFO from which will be read.
            std::ifstream _fifo;

/*}}}*/
            // bool _isFifoValid;/*{{{*/

            /// Indicates whether @ref _fifo is valid.
            bool _isFifoValid;

/*}}}*/
            // pthread_t _thread;/*{{{*/

            /// The thread running @ref _listen
            pthread_t _thread;

/*}}}*/
            // bool _isListening;/*{{{*/
            /// Indicates whether @ref listen() is active.
            bool _isListening;

/*}}}*/
            // bool _mustClose;/*{{{*/

            /// Indicates whether the thread running @ref _listen must terminate
            bool _mustClose;

/*}}}*/
            // virtual std::string _createPath() const = 0;/*{{{*/

            /**
             * @brief Returns the path and file name of the FIFO.
             *
             * Called by @ref initialize() which stores the result in @ref _path
             * which is used throughout the class in the other methods.
             *
             * @return Path and file name where the FIFO should be placed.
             */
            virtual std::string _createPath() const = 0;

/*}}}*/
            // virtual void _handleInput(const std::string &input) = 0;/*{{{*/

            /**
             * @brief Handles input that has been written into the FIFO.
             *
             * @param input Something that has been written into the FIFO.
             */
            virtual void _handleInput(const std::string &input) = 0;

/*}}}*/
            // static void *_listen(void *fifo);/*{{{*/

            /**
             * @brief Listens blocking on the passed FIFO.
             *
             * Runs an infinite loop on @ref _read() of the object @a fifo.
             *
             * @note This method terminates only if @ref _mustClose is true and
             *       the blocking call to @ref _read() finishes.
             *
             * @warning Should only be called by a pthread created in @ref 
             *          listen.
             *
             * @warning The parameter @a fifo should not be anything other than
             *          a pointer to an object of AbcInput or derivates.
             *
             * @param fifo Pointer to object of AbcInput or childs.
             * @return NULL
             * @see AbcInput::listen()
             * @see AbcInput::close()
             * @see AbcInput::_read()
             */
            static void *_listen(void *fifo);

/*}}}*/
    };
}

#endif // FILE_ABCINPUT_HXX

// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
