// LICENSE/*{{{*/
/*
  libsxc
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

#ifndef CONTACT_FILE_INFO_HXX
#define CONTACT_FILE_INFO_HXX

// INCLUDE/*{{{*/

#include <File/AbcInfo.hxx>

#include <string>

/*}}}*/

namespace Contact
{
  namespace File
  {
    /**
     */
    class Info : public ::File::AbcInfo
    {
      public:
        Info(const std::string &accountJid, const std::string &contactJid);

        virtual void remove();

        template <typename T> void setPresence(T &value);
        template <typename T> void setMessage(T &value);
        template <typename T> void setRoster(T &value);

      protected:
        virtual const std::string _createPath();

      private:
        const std::string _accountJid;
        const std::string _contactJid;
    };
  }
}

#include <Contact/File/Info.ixx>

#endif // CONTACT_FILE_INFO_HXX
// Use no tabs at all; two spaces indentation; max. eighty chars per line.
// vim: et ts=2 sw=2 sts=2 tw=80 fdm=marker
