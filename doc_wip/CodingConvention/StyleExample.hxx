// LICENSE/*{{{*/
/*
  Copyright (C) 2008 Andreas Waidler, Dennis Felsing

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


#ifndef SOMENAMESPACE_STYLEEXAMPLE_HXX
#define SOMENAMESPACE_STYLEEXAMPLE_HXX

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
   *
   *
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
      // void doSomethingWithManyArguments(argA, argB, argC, argD);/*{{{*/

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


#endif // SOMENAMESPACE_STYLEEXAMPLE_HXX
// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
