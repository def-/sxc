#line 2 "sxc:File/AbcInput.cxx"
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

// INCLUDES/*{{{*/

#ifdef HAVE_CONFIG_H
# include <config.hxx>
#endif

#include <cerrno>
#include <sys/stat.h>
#include <pthread.h>
#include <signal.h>

#include <list>
#include <string>
#include <fstream>
#include <sstream>

#include <File/AbcInput.hxx>
#include <File/Exception/BadFile.hxx>
#include <File/Exception/FileLocked.hxx>
#include <File/Exception/errnoToException.hxx>

#include <Exit/Code.hxx>
#include <libsxc/Debug/Logger.hxx>

/*}}}*/


namespace File
{
  AbcInput::AbcInput()/*{{{*/
  : _isFifoValid(false),
    _isListening(false),
    _mustClose(false)
  {
  }

  /*}}}*/
  AbcInput::~AbcInput()/*{{{*/
  {
    if (_isListening)
      close();
  }

  /*}}}*/
  void AbcInput::initialize(bool notPhysical)/*{{{*/
  {
    _path = _createPath();

    if (!notPhysical) {
      try {
        _validate();
      } catch (libsxc::Exception::Exception &e) {
        // If the file is missing, create it. Anything else means that someone
        // tampered with the file.
        if (Exit::FileMissing != e.getExitCode())
          throw e;
        _create();
      }
    }
  }

  /*}}}*/
  void AbcInput::_create()/*{{{*/
  {
    // Try to create FIFO with chmod 600.
    if (0 == mkfifo(_path.c_str(), S_IRUSR | S_IWUSR))
      return;

    // Creation of FIFO failed.
    std::string message  = "Could not create FIFO " + _path;
    throw Exception::errnoToException(errno, message.c_str());
  }

  /*}}}*/
  void AbcInput::_validate()/*{{{*/
  {
    // Try to get file stats, needed for analyzing the chmod of the file.
    struct stat fstat;
    if (0 != stat(_path.c_str(), &fstat)) {
      std::string message  = "Could not get FIFO fstat: " + _path;
      throw Exception::errnoToException(errno, message.c_str());
    }

    // Is this really a FIFO?
    if (!S_ISFIFO(fstat.st_mode)) {
      std::string message  = "Not a FIFO: " + _path;
      throw Exception::BadFile(message.c_str());
    }

    // FIXME: Remove check for chmod?
    // Check for chmod 600(octal):
    int chmod = fstat.st_mode
          & (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    int chmodExpected = (S_IRUSR | S_IWUSR);

    std::stringstream msg;
    msg << "fstat.st_mode = " << std::oct << fstat.st_mode << '\n';
    msg << "chmod         = " << std::oct << chmod         << '\n';
    msg << "expected      = " << std::oct << chmodExpected << '\n';
    LOG(msg.str());

    if (chmod != chmodExpected) {
      std::stringstream msg;
      msg << "Bad chmod: " << std::oct << chmod;
      // FIXME: Exceptions have to accept parameter being a string.
      std::string message = msg.str();
      throw Exception::BadFile(message.c_str());
    }

    _isFifoValid = true;
  }

  /*}}}*/
  std::string AbcInput::_read()/*{{{*/
  {
    std::string input;
    std::string buf;

    _fifo.open(_path.c_str());
    while (!_fifo.eof()) {
      getline(_fifo, buf);
      input.append(buf);
      input.push_back('\n');
    }
    _fifo.close();

    if (!input.empty())
      input.erase(--input.end()); // Remove the last newline.

    return input;
  }

  /*}}}*/
  void AbcInput::listen(bool blocking)/*{{{*/
  {
    // Prevent input from being handled twice:
    if (_isListening) {
      std::string message = "Already listening on " + _path;
      throw Exception::FileLocked(message.c_str());
    }
    _isListening = true;

    LOG("Creating thread.");

    // Start the thread in the background.
    pthread_create(&_thread, NULL, _listen, (void*)this);

    LOG("Thread created.");

    // Join the thread when this functions should read in a blocking way.
    if (true == blocking)
      pthread_join(_thread, NULL);

    LOG("listen() ends here.");
  }

  /*}}}*/
  void AbcInput::close()/*{{{*/
  {
    if (_isListening) {
      _mustClose = true;
      // Open an close FIFO in order to unblock subthread.
      std::ofstream out(_path.c_str());
      out.close();
      pthread_join(_thread, NULL);
    }

    _mustClose   = false;
    _isListening = false;
  }

  /*}}}*/
  std::list<std::string> AbcInput::split(
    const std::string &data, const char delim)/*{{{*/
  {
    std::istringstream in(data);
    std::string buf;
    std::list<std::string> splitted;

    do {
      getline(in, buf, delim);
      if (!buf.empty())
        splitted.push_back(buf);
    } while (!in.eof());

    return splitted;
  }

  /*}}}*/
  void *AbcInput::_listen(void *fifo)/*{{{*/
  {
    LOG("Thread running.");
    // FIXME: Add exception handling. || called methods must not throw
    AbcInput *that = (AbcInput *) fifo;
    while (!that->_mustClose) {
      std::string input = that->_read();

      if (that->_mustClose) break;
      if (input.empty()) continue;

      std::list<std::string> inputs = AbcInput::split(input, '\0');
      for (std::list<std::string>::iterator it = inputs.begin();
         it != inputs.end();
         ++it)
      {
        if ('\n' == it->at(it->size() - 1)) {
          // Remove trailing newline.
          that->_handleInput(it->substr(0, it->size() - 1));
        } else {
          that->_handleInput(*it);
        }
      }
    }

    LOG("Thread terminating.");

    return NULL;
  }

  /*}}}*/
}

// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
