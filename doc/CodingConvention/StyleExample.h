// LICENSE/*{{{*/
/*
  Copyright (C) 2008 Andreas Waidler, Dennis Felsing

  This program is free software: you can redistribute it and/or modify it 
  under the terms of the GNU General Public License as published by the Free 
  Software Foundation, either version 3 of the License, or (at your option) 
  any later version.

  This program is distributed in the hope that it will be useful, but WITHOUT 
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
  FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for 
  more details.

  You should have received a copy of the GNU General Public License along with 
  this program. If not, see <http://www.gnu.org/licenses/>.
 */
/*}}}*/

/**
 * @file StyleExample.h
 * @brief Example how the classes should look like.
 * @author Andreas Waidler
 * @date 2008-05-17
 *
 * This file is a prototype of the header files that will be used in sxc. Stick 
 * to the examples shown here or use your brain.
 *
 * Inspired by @ref http://www.possibility.com/
 */


#ifndef SOMENAMESPACE_STYLEEXAMPLE_H
#define SOMENAMESPACE_STYLEEXAMPLE_H

// INCLUDES/*{{{*/

#include<string>

/*}}}*/


/**
 * @namespace SomeNamespace
 * @brief Namespace of StyleExample.
 *
 * Base namespace of the coding standards of the sxc project. Acts also as an 
 * example how namespaces should be formatted and documented.
 *
 * @note The docblock of a namespace should be placed in the directory, where 
 *       its files are placed. Its file name should be its name with an .h 
 *       appended. If this file exists, simply document it in the existing file 
 *       (where the namespace should be declared, anyways).
 */
namespace SomeNamespace
{
    /**
     * @class SomeNamespace
     * @brief Coding style example class.
     *
     * An example class showing the coding style used in sxc. It is inspired by 
     * http://www.possibility.com/
     *
     * This is a JavaDoc style comment.
     * The first line is a brief description, everything following is the same in 
     * verbose.
     *
     * @see something
     */
    class StyleExample
    {
        public:
            // StyleExample();/*{{{*/

            /**
             * @brief Default constructor.
             *        This is is STILL a brief description.
             *
             * This is the verbose description of the constructor that does 
             * foo and bar.
             *
             * @note This is a note.
             */
            StyleExample();

/*}}}*/
            // ~StyleExample();/*{{{*/

            /** 
             * @brief Brief description. 
             *
             * The Second sentence is the detailed description. And it is very
             * detailed, isn't it?
             *
             * @warning Use autobrief only for comments fitting into one line.
             */
            ~StyleExample();

/*}}}*/
            // bool doSomething(std::string someString, int someNumber);/*{{{*/

            /**
             * @brief A member doing something with what it gets.
             *
             * @warning Don't do this and that!
             *
             * @param someString A string about something interesting
             * @param someNumber A weird number that will be processed
             * @exception SomeException This is the description.
             * @return Whether everything the procession did succed or not
             */
            bool doSomething(std::string someString, int someNumber);

/*}}}*/
            // void doSomethingWithManyArguments(/*{{{*/

            /**
             * @brief Does something with many arguments.
             *
             * No one knows what this method does.
             * 
             * @param argA An important integer.
             * @param argB A less important integer.
             * @param argC A string containing some mysterious data.
             * @param argD Another string.
             */
            void doSomethingWithManyArguments(
                int         argA,
                int         argB,
                std::string argC,
                std::string argD);

/*}}}*/
            // int getSomeValue();/*{{{*/

            /** A normal setter.
             *
             * @return Height of some object.
             */
            int getSomeValue();

/*}}}*/
            // bool isValid();/*{{{*/

            /** Check if the object is still valid.
             *
             * @return Whether this object is valid.
             */
            bool isValid();

/*}}}*/

        protected:

        private:
            // int _someValue;/*{{{*/

            /**
             * @brief A variable.
             *
             * This is a very detailled description of this private variable.
             */
            int         _someValue;
/*}}}*/
            int         _anotherValue;
            /// The name of this object.
            std::string _someString;
    };
}


#endif // SOMENAMESPACE_STYLEEXAMPLE_H
// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
