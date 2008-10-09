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

#ifndef FILE_ABCOUTPUT_H
#define FILE_ABCOUTPUT_H

// INCLUDES/*{{{*/

#include <string>
#include <fstream>

/*}}}*/

namespace File
{
    /**
     * @brief Abstract base class handling output to files.
     *
     * Handles writing into a file whose path is returned by @ref _createPath().
     *
     * Children of this class have to implement the abstract method @ref
     * _createPath().
     */
    class AbcOutput
    {
        public:
            // AbcOutput();/*{{{*/

            /**
             * @brief Default constructor, does low-level initialization.
             *
             * Before using any instance of derived classes, you should also
             * call @ref initialize().
             */
            AbcOutput();

/*}}}*/
            // virtual ~AbcOutput();/*{{{*/

            /**
             * @brief Virtual destructor, closes file if open.
             */
            virtual ~AbcOutput();

/*}}}*/
            // virtual void initialize();/*{{{*/

            /**
             * @brief Initializes the object.
             *
             * Apart from the constructor a more high-level initialization will
             * be done, which includes calling @ref _createPath() because it
             * can't be called in the constructor (abstract method).
             *
             * @note Has to be called before any other method. You may want to
             *       call it in the constructor of the childs.
             */
            virtual void initialize();

/*}}}*/
            // virtual void write(const std::string &data);/*{{{*/

            /**
             * @brief Writes into file.
             *
             * @note You have to @ref open() the file before writing.
             *
             * @param data The data to write.
             */
            virtual void write(const std::string &data);

/*}}}*/
            // void open();/*{{{*/

            /**
             * @brief Opens the file.
             *
             * Before this method is called there is no physical file associated
             * with this object.
             */
            void open();

/*}}}*/
            // void close();/*{{{*/

            /**
             * @brief Closes the file if open.
             *
             * After calling this method there will no physical file be
             * associated with this object.
             */
            void close();

/*}}}*/
            // bool isOpen() const;/*{{{*/

            /**
             * @brief Checks whether the file is opened or not.
             *
             * @return @c true if open, @c false otherwiese.
             */
            bool isOpen() const;

/*}}}*/

        protected:
            // std::ofstream _ofstream;/*{{{*/

            /// The file from which will be read.
            std::ofstream _ofstream;

/*}}}*/
            // virtual void _dispose() throw();/*{{{*/

            /// Frees all resources.
            virtual void _dispose() throw();

/*}}}*/

        private:
            // std::string _path;/*{{{*/

            /// The path including file name where the file should be located.
            std::string *_path;

/*}}}*/
            // virtual std::string _createPath() const = 0;/*{{{*/

            /**
             * @brief Creates the path where the file should be located.
             *
             * @return The path where the file should be located.
             */
            virtual std::string _createPath() const = 0;

/*}}}*/
    };
}

#endif // FILE_ABCOUTPUT_H

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
