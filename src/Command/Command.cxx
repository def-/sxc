#line 2 "sxc:Command/Command.cxx"
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

// INCLUDE/*{{{*/

#ifdef HAVE_CONFIG_H
# include <config.hxx>
#endif

#include <Command/Command.hxx>

#include <Command/utilities.hxx>
#include <Command/Exception/CouldNotAdd.hxx>
#include <Command/Exception/CouldNotSet.hxx>
#include <Command/Exception/CouldNotExecute.hxx>

#include <libsxc/Exception/RuntimeError.hxx>
#include <libsxc/Exception/Underflow.hxx>
#include <libsxc/Exception/Overflow.hxx>

#include <libsxc/Debug/Logger.hxx>

#include <map>
#include <string>
#include <exception>

/*}}}*/

namespace Command
{
  Command::Command()/*{{{*/
  : _isComplete(false)
  {
  }

/*}}}*/
  void Command::add(const std::string& value)/*{{{*/
  {
    try {
      LOG("Trying to add argument " + value);

      // TODO: Add some private property flag which indicates whether the
      // command while already being complete may still be overloaded.
      if (isComplete())
        throw libsxc::Exception::Overflow("Command already complete.");

      unsigned int index;
      // When the container is empty, the index of this argument will be 0.
      if (_arguments.empty()) {
        LOG("This was easy; first argument.");
        index = 0;
      } else {
        // std::map keeps its contents ordered by the key. To append something,
        // we have to get the key (which is the index of the argument) of the
        // last element and add one to it.
        LOG("Fetching new index");
        std::map<unsigned int, std::string>::iterator it = --(_arguments.end());
        index = it->first + 1;
        LOG("Index fetched.");
      }
      _arguments.insert(
        std::pair<unsigned int, std::string>(index, value));

      try {
        // Argument added. Call event handler.
        LOG("Everything all right. Calling event handler.");
        _onAdd();
      } catch (std::exception& e) {
        // Let's be carefull and delete the argument which caused _onAdd() to
        // fail from the container.
        LOG("Event handler failed. Erasing added argument.");
        _arguments.erase(_arguments.find(index));
        LOG("Argument erased. Rethrowing.");
        throw libsxc::Exception::RuntimeError("_onAdd() failed.", e);
      }
    } catch (std::exception &e) {
      throw Exception::CouldNotAdd(value.c_str(), e);
    }
    LOG("Added sucessfully.");
  }

/*}}}*/
  void Command::set(unsigned int index, const std::string& value)/*{{{*/
  {
    try {
      // Get the current value of the with the passed index, if existing. If
      // not, set the string holding the value to an empty one.
      std::map<unsigned int,std::string>::iterator now = _arguments.find(index);
      const std::string oldValue = (now == _arguments.end() ? "" : now->second);

      // Create the new argument and insert it.
      std::pair<unsigned int, std::string> argument(index, value);
      _arguments.insert(argument);

      try {
        // Argument added. Call event handler.
        _onSet(index, oldValue);
      } catch (std::exception &e) {
        // Let's be carefull and delete the argument which caused _onSet() to
        // fail from the container.
        _arguments.erase(_arguments.find(index));
        throw libsxc::Exception::RuntimeError("_onSet() failed.", e);
      }
    } catch (std::exception &e) {
      throw Exception::CouldNotSet(index, value.c_str(), e);
    }
  }

/*}}}*/
  bool Command::isComplete() const/*{{{*/
  {
    return _isComplete;
  }

/*}}}*/
  const std::map<unsigned int, std::string>& Command::container() const/*{{{*/
  {
    return _arguments;
  }

/*}}}*/
  void Command::operator()() const/*{{{*/
  {
    try {
      if (!isComplete())
        throw libsxc::Exception::Underflow("Command not complete.");
      _execute();
    } catch (std::exception &e) {
      throw Exception::CouldNotExecute(e);
    }
  }

/*}}}*/
  void Command::setComplete(bool flag)/*{{{*/
  {
    _isComplete = flag;
  }

/*}}}*/
}

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
