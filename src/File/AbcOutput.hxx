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
