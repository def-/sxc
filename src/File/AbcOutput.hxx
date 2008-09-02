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
     * @brief Abstract base class handling output to text files.
     *
     * Handles writing into a file whose path is returned by @ref _createPath().
     * Formats the output before writing by calling @ref _format().
     *
     * Children of this class have to implement the abstract methods @ref
     * _createPath() and @ref _format().
     *
     * @author Andreas Waidler
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

            virtual ~AbcOutput();



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
            void initialize();


            void write(std::string text);


            void open();


            void close();


            bool isOpen();



        protected:

        private:
            /// The path including file name where the file should be located.
            std::string _path;
            /// The file from which will be read.
            std::ofstream _file;

            virtual std::string _createPath() const = 0;


            virtual std::string _format(const std::string &output) const = 0;


    };
}

#endif // FILE_ABCOUTPUT_H

// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
