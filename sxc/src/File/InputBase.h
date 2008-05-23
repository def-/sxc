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
#include <istream>
#include <pthread.h>
#include "File.h"

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
     * and how the input is handled. These pure virtual methods have to be 
     * overwritten by each direct child.
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
             * Calls @ref _createPath() to set @ref _path. Tries to create the 
             * FIFO or checks its permissions by calling @ref _tryCreate() or 
             * @ref _checkPermissions().
             *
             * @note This method has to be called before any other method can be
             *       used! You may want to call it in the constructor of the 
             *       childs.
             *
             * @warning Do not override this method!
             */
            void initialize();

/*}}}*/
            // void listen(bool blocking = false);/*{{{*/

            /**
             * @brief Starts listening on the FIFO.
             *
             * Listens on the FIFO until @ref close() is called. If @a blocking 
             * ist set to @c true this method will read blocking, i.e. it will 
             * only finish when close() is called. Per default, @a blocking is 
             * @c false so a thread is started which runs non-blocking and calls 
             * this function with @a blocking set to @c true.
             *
             * @warning Do not override this method!
             *
             * @param blocking Specifies whether this method should listen 
             *                 blocking or non-blocking.
             */
            void listen(bool blocking = false);

/*}}}*/
            // void read();/*{{{*/

            /**
             * @brief Reads the FIFO blocking until the other end is closed.
             *
             * Input is handled by calling @ref _handle
             *
             * @warning Do not override this method!
             */
            void read();

/*}}}*/
            // void close();/*{{{*/

            /**
             * @brief Closes the FIFO.
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
            std::istream _fifo;
            /// The thread running @ref _pthreadListen
            pthread_t _thread;
            /// Indicates whether @ref _thread is running.
            bool _threadIsRunning;
            // virtual std::string _createPath() = 0;/*{{{*/

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
            virtual std::string _createPath() = 0;

/*}}}*/
            // virtual void _handle(std::string input) = 0;/*{{{*/

            /**
             * @brief Handles input that has been written into the FIFO.
             *
             * @note Pure virtual.
             *
             * @param input Something that has been written into the FIFO.
             */
            virtual void _handle(std::string input) = 0;

/*}}}*/
            // void _tryCreate();/*{{{*/

            /**
             * @brief Tries to create the FIFO.
             *
             * @exception FileInputException ErrorType 
             *            ErrorFileCreationPermission when the file could not be
             *            created.
             */
            void _tryCreate();

/*}}}*/
            // void _checkPermissions();/*{{{*/

            /**
             * @brief Checks the permissions of the FIFO.
             *
             * This method throws an exception if invalid file permissions are 
             * set. "Valid file permissions" means that this program runs with 
             * the UID of the FIFOs owner and that the FIFO is not writable for 
             * other users.
             *
             * @exception File::FileInputException ErrorType on invalid permissions.
             */

            void _checkPermissions();

/*}}}*/
            // void *_pthreadListen(void *ptr);/*{{{*/

            /**
             * @brief Calls @ref listen() with @a blocking being @c true.
             *
             * Called by @c pthread_create() in @ref listen() when 
             * non-blocking listening has been requested.
             *
             * @param ptr Needed by @c pthread_create() but not used.
             * @return 0
             */
            void *_pthreadListen(void *ptr);

/*}}}*/
    };
}

#endif // FILE_INPUTBASE_H

// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
