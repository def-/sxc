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

/* $Id$ */


#ifndef CONTROL_ROSTER_H
#define CONTROL_ROSTER_H


// INCLUDE/*{{{*/

#include <gloox/rostermanager.h>

#include "../Contact/Contact.h"

/*}}}*/


namespace Control
{
    /**
     * @class Roster
     * @author Dennis Felsing
     */
    class Roster : public gloox::RosterManager
    {
        public:
            Roster(gloox::ClientBase *parent);

            virtual bool handleIq(const gloox::IQ &iq) {}
            virtual void handleIqID(const gloox::IQ &iq, int context) {}
            virtual void handlePresence(const gloox::Presence &presence) {}
            virtual void handleSubscription(const gloox::Subscription &subscription) {}
            virtual void handlePrivateXML(const gloox::Tag *xml) {}
            virtual void handlePrivateXMLResult(const std::string &uid, gloox::PrivateXMLHandler::PrivateXMLResult pxResult) {}

        private:

    };
}


#endif // CONTROL_ROSTER_H
// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
