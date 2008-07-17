// FIXME Lock for read() method - listen()/read() may start even when object is already reading. this has to be disabled!
// FIXME close() only if FIFO is open.
// FIXME maybe split close() to close() and _kill() - _kill() into destructor -- kill MUST NEVER throw/fail.
// FIXME catch references
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

#ifndef FILE_INPUTBASE_H
#define FILE_INPUTBASE_H

// INCLUDES/*{{{*/

#include <string>
#include <fstream>
#include <pthread.h>

/*}}}*/


namespace File
{
    /**
     * @class File::InputBase
     * @author Andreas Waidler
     * @brief Abstract Base Class handling input (FIFOs).
     *
     * Handles creation and checking of, listening (non-blocking) on and reading
     * (blocking) off FIFOs.
     * Contains pure virtual methods that will define the location of the FIFO 
     * and how the input is handled.
     */
    class InputBase
    {
        public:
            // InputBase();/*{{{*/

            /// Constructor, initializes private variables with default values.
            InputBase();

/*}}}*/
            // virtual ~InputBase();/*{{{*/

            /**
             * @brief Destructor, frees resources and cleans up.
             *
             * Takes care of a clean termination of the thread if running. 
             * Closes the FIFO if open.
             */
            virtual ~InputBase();

/*}}}*/
            // void initialize();/*{{{*/

            /**
             * @brief Initializes the object.
             *
             * Calls @ref _createFilePath() to set @ref _path. Tries to create 
             * the FIFO or checks its permissions by calling @ref _tryCreate() 
             * or @ref _validateFile().
             *
             * @note This method has to be called before any other method can 
             *       be used! You may want to call it in the constructor of 
             *       the childs.
             *
             * @warning Do not override this method!
             */
            void initialize();

/*}}}*/
            // void listen(bool blocking = false);/*{{{*/

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
             * @warning Do not override this method!
             *
             * @param blocking Specifies whether this method should listen 
             * blocking or non-blocking.
             */
            void listen(bool blocking = false);

/*}}}*/
            // void close();/*{{{*/

            /**
             * @brief Closes the FIFO.
             *
             * Closes the FIFO and cancles the thread, if running.
             *
             * @warning Do not override this method!
             */
            void close();

/*}}}*/

        protected:


        private:
            /// The path including file name where the FIFO is located.
            std::string _path;
            /// The FIFO from which will be read.
            std::ifstream _fifo;
            /// Indicates whether @ref _fifo is valid.
            bool _isFifoValid;
            /// The thread running @ref _listen
            pthread_t _thread;
            /// Indicates whether @ref _thread is running.
            bool _isThreadRunning;
            // virtual std::string _createFilePath() = 0;/*{{{*/

            /**
             * @brief Returns the path and file name of the FIFO.
             *
             * Called by @ref initialize() which stores the result in @ref _path
             * which is used throughout the class in the other methods.
             *
             * @note Pure virtual.
             *
             * @return Path and file name where the FIFO should be placed.
             */
            virtual std::string _createFilePath() = 0;

/*}}}*/
            // virtual void _handleInput(std::string input) = 0;/*{{{*/

            /**
             * @brief Handles input that has been written into the FIFO.
             *
             * @note Pure virtual.
             *
             * @param input Something that has been written into the FIFO.
             */
            virtual void _handleInput(std::string input) = 0;

/*}}}*/
            // void _createFile();/*{{{*/

            /** Creates the FIFO.
             *
             * @exception Exception::FileInputException When the file could not
             *            be created. @c Exception::Type is the result of 
             *            @ref Exception::errnoToType().
             */
            void _createFile();

/*}}}*/
            // void _validateFile();/*{{{*/

            /**
             * @brief Checks the FIFO for validity and throws an exception if 
             *        something is not like expected. 
             *
             * The FIFOs owner-uid has to be the one who runs this program. 
             * Additionally, the FIFO must @b not be readable or writable for
             * other users. (chmod 600).
             *
             * @exception Exception::FileInputException When file is invalid.
             *            @ref Exception::Type will be @ref BadFile or @c errno
             *            converted to Type by @ref Exception::errnoToType().
             */

            void _validateFile();

/*}}}*/
            // void read();/*{{{*/

            /**
             * @brief Reads the FIFO blocking until the other end is closed.
             *
             * Input is handled by calling @ref _handleInput().
             *
             * @warning Do not override this method!
             */
            void read();

/*}}}*/
            // static void *_listen(void *fifo);/*{{{*/

            /**
             * @brief Listens blocking on the passed FIFO.
             *
             * Runs an infinite loop on @ref read() of the object @a fifo.
             *
             * @warning Should only be called by a pthread created in @ref 
             *          listen. This method will never stop by itsself, thus
             *          its thread has to be canceled.
             * @warning The parameter @a fifo should not be anything other than
             *          a this-pointer.
             *
             * @param fifo Pointer to object of class InputBase.
             * @return NULL
             * @see InputBase::listen()
             * @see InputBase::close()
             * @see InputBase::read()
             */
            static void *_listen(void *fifo);

/*}}}*/
    };
}

#endif // FILE_INPUTBASE_H

// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
