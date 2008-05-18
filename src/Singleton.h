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


#ifndef SINGLETON_H
#define SINGLETON_H


/**
 * @class SomeNamespace
 *
 * @author Dennis Felsing
 *
 * @brief A singleton base class.
 *
 * Singleton classes inherit from this class.
 *
 * @code
 * class Example : public Singleton
 * {
 *     public:
 *         void doSomething();
 * };
 * @endcode
 *
 * The methods of the class can then be used without creating an object.
 *
 * @code
 * Example::getInstance().doSomething();
 * @endcode
 */


template <class Type>
class Singleton
{
    public:
        //static Type &getInstance()/*{{{*/
        /** Get the only instance.
         *
         * @return An object of Instance, a class inheritting from the real
         *         class.
         */
        static Type &getInstance()
        {
            static Instance instance;
            return instance;
        }

/*}}}*/
    private:
        // class Instance : public Type {};/*{{{*/
        /**
         * A class inheritting from the class that is intended to be a
         * singleton.
         */
        class Instance : public Type {};

/*}}}*/
};


#endif // SINGLETON_H
// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
