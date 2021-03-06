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

#ifndef FILE_ABCINPUT_HXX
#define FILE_ABCINPUT_HXX

// INCLUDES/*{{{*/

#include <pthread.h>

#include <list>
#include <string>
#include <fstream>

/*}}}*/

namespace File
{
  /**
   * @brief Abstract Base Class handling input (FIFOs).
   *
   * Handles creation, checking, listening (non-blocking) on and reading
   * (blocking) of named pipes (FIFO).
   */
  class AbcInput
  {
    public:
      // static list<string> splitNull(const string &)/*{{{*/

      /**
       * @brief Splits @a data on each occurrence of @a delim.
       *
       * @note: @a delim will be extracted and discarded.
       *
       * @param data Any input to split.
       * @param delim Character to delimit the substrings.
       * @return Constant reference to a list holding the parts.
       */
      static std::list<std::string> split(
        const std::string &data, const char delim);

/*}}}*/
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
      // std::string _read();/*{{{*/

      /**
       * @brief Reads the FIFO blocking.
       *
       * Stops reading when EOF is reached. This typically happens when
       * the writer closes the pipe.
       *
       * @note Since the underlying object is a named pipe, opening it for
       *       reading blocks until the file is opened in write mode.
       */
      std::string _read();

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

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
