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

// INCLUDE/*{{{*/

#include <string>
#include <gloox/gloox.h>

/*}}}*/

std::string &generateErrorText(/*{{{*/
    gloox::ConnectionError connectionError,
    gloox::StreamError streamError,
    const std::string &streamErrorText,
    gloox::AuthenticationError authError)
{
    static std::string text;

    switch (connectionError) {
    case gloox::ConnNoError:
        break;
    case gloox::ConnStreamError: {
        text = "A stream error occured: ";
        switch (streamError) {
        case gloox::StreamErrorUndefined:
            text += "Undefined/unknown error.";
            break;
        case gloox::StreamErrorBadFormat:
            text += "The entity has sent XML that cannot be processed.";
            break;
        case gloox::StreamErrorBadNamespacePrefix:
            text += "The entity has sent a namespace prefix that is "
                    "unsupported, or has sent no namespace prefix on an "
                    "element that requires such a prefix.";
            break;
        case gloox::StreamErrorConflict:
            text += "The server is closing the active stream for this "
                    "entity because a new stream has been initiated that "
                    "conflicts with the existing stream.";
            break;
        case gloox::StreamErrorConnectionTimeout:
            text += "The entity has not generated any traffic over the "
                    "stream for some period of time.";
            break;
        case gloox::StreamErrorHostGone:
            text += "The value of the 'to' attribute provided by the "
                    "initiating entity in the stream header corresponds to "
                    "a hostname that is no longer hosted by the server.";
            break;
        case gloox::StreamErrorHostUnknown:
            text += "The value of the 'to' attribute provided by the "
                    "initiating entity in the stream header does not "
                    "correspond to a hostname that is hosted by the "
                    "server.";
            break;
        case gloox::StreamErrorImproperAddressing:
            text += "A stanza sent between two servers lacks a 'to' or "
                    "'from' attribute.";
            break;
        case gloox::StreamErrorInternalServerError:
            text += "The server has experienced a misconfiguration or an "
                    "otherwise-undefined internal error that prevents it "
                    "from servicing the stream.";
            break;
        case gloox::StreamErrorInvalidFrom:
            text += "The JID or hostname provided in a 'from' address does "
                    "not match an authorized JID or validated domain "
                    "negotiated between servers via SASL or dialback, or "
                    "between a client and a server via authentication and "
                    "resource binding.";
            break;
        case gloox::StreamErrorInvalidId:
            text += "The stream ID or dialback ID is invalid or does not "
                    "match an ID previously provided.";
            break;
        case gloox::StreamErrorInvalidNamespace:
            text += "The streams namespace name is something other than "
                    "\"http://etherx.jabber.org/streams\" or the dialback "
                    "namespace name is something other than "
                    "\"jabber:server:dialback\".";
            break;
        case gloox::StreamErrorInvalidXml:
            text += "The entity has sent invalid XML over the stream to a "
                    "server that performs validation.";
            break;
        case gloox::StreamErrorNotAuthorized:
            text += "The entity has attempted to send data before the "
                    "stream has been authenticated, or otherwise is not "
                    "authorized to perform an action related to stream "
                    "negotiation.";
            break;
        case gloox::StreamErrorPolicyViolation:
            text += "The entity has violated some local service policy.";
            break;
        case gloox::StreamErrorRemoteConnectionFailed:
            text += "The server is unable to properly connect to a remote "
                    "entity that is required for authentication or "
                    "authorization.";
            break;
        case gloox::StreamErrorResourceConstraint:
            text += "The server lacks the system resources necessary to "
                    "service the stream.";
            break;
        case gloox::StreamErrorRestrictedXml:
            text += "The entity has attempted to send restricted XML "
                    "features.";
            break;
        case gloox::StreamErrorSeeOtherHost:
            text += "The server will not provide service to the initiating "
                    "entity but is redirecting traffic to another host.";
            break;
        case gloox::StreamErrorSystemShutdown:
            text += "The server is being shut down and all active streams "
                    "are being closed.";
            break;
        case gloox::StreamErrorUndefinedCondition:
            text += "The error condition is not one of those defined by "
                    "the other conditions in this list.";
            break;
        case gloox::StreamErrorUnsupportedEncoding:
            text += "The initiating entity has encoded the stream in an "
                    "encoding that is not supported by the server.";
            break;
        case gloox::StreamErrorUnsupportedStanzaType:
            text += "The initiating entity has sent a first-level child of "
                    "the stream that is not supported by the server.";
            break;
        case gloox::StreamErrorUnsupportedVersion:
            text += "The initiating entity specifies a version of XMPP "
                    "that is not supported by the server.";
            break;
        case gloox::StreamErrorXmlNotWellFormed:
            text += "The initiating entity has sent XML that is not "
                    "well-formed.";
            break;
        default:
            text += "Unknown error.";
        break;
        }
        if (!streamErrorText.empty())
            text += " (Addition information: " + streamErrorText + ")";
    }
    case gloox::ConnStreamVersionError:
        text = "The incoming stream's version is not supported.";
        break;
    case gloox::ConnStreamClosed:
        text = "The stream has been closed by the server.";
        break;
    case gloox::ConnProxyAuthRequired:
        text = "The HTTP/SOCKS5 proxy requires authentication.";
        break;
    case gloox::ConnProxyAuthFailed:
        text = "The HTTP/SOCKS5 proxy authentication failed.";
        break;
    case gloox::ConnProxyNoSupportedAuth:
        text = "The HTTP/SOCKS5 proxy requires an unsupported auth "
               "mechanism.";
        break;
    case gloox::ConnIoError:
        text = "An I/O error occured.";
        break;
    case gloox::ConnParseError:
        text = "An XML parse error occured.";
        break;
    case gloox::ConnConnectionRefused:
        text = "The connection was refused by the server (on the socket "
               "level).";
        break;
    case gloox::ConnDnsError:
        text = "Resolving the server's hostname failed.";
        break;
    case gloox::ConnOutOfMemory:
        text = "Out of memory.";
        break;
    case gloox::ConnNoSupportedAuth:
        text = "The auth mechanisms the server offers are not supported "
               "or the server offered no auth mechanisms at all.";
        break;
    case gloox::ConnTlsFailed:
        text = "The server's certificate could not be verified or the TLS "
               "handshake did not complete successfully.";
        break;
    case gloox::ConnTlsNotAvailable:
        text = "The server doesn't offer TLS.";
        break;
    case gloox::ConnCompressionFailed:
        text = "Negotiating or initializing compression failed.";
        break;
    case gloox::ConnAuthenticationFailed:
        text = "Authentication failed: ";
        switch (authError) {
        case gloox::AuthErrorUndefined:
            text += "Error condition unknown.";
            break;
        case gloox::SaslAborted:
            text += "The receiving entity acknowledges an abort sent by "
                    "the initiating entity.";
            break;
        case gloox::SaslIncorrectEncoding:
            text += "The data provided by the initiating entity could not "
                    "be processed because the [BASE64] encoding is "
                    "incorrect.";
            break;
        case gloox::SaslInvalidAuthzid:
            text += "The authzid provided by the initiating entity is "
                    "invalid, either because it is incorrectly formatted "
                    "or because the initiating entity does not have "
                    "permissions to authorize that ID.";
            break;
        case gloox::SaslInvalidMechanism:
            text += "The initiating entity did not provide a mechanism or "
                    "requested a mechanism that is not supported by the "
                    "receiving entity.";
            break;
        case gloox::SaslMalformedRequest:
            text += "The request is malformed.";
            break;
        case gloox::SaslMechanismTooWeak:
            text += "The mechanism requested by the initiating entity is "
                    "weaker than server policy permits for that initiating "
                    "entity.";
            break;
        case gloox::SaslNotAuthorized:
            text += "The authentication failed because the initiating "
                    "entity did not provide valid credentials.";
            break;
        case gloox::SaslTemporaryAuthFailure:
            text += "The authentication failed because of a temporary "
                    "error condition within the receiving entity.";
            break;
        case gloox::NonSaslConflict:
            text += "Resource conflict.";
            break;
        case gloox::NonSaslNotAcceptable:
            text += "Required Information not provided.";
            break;
        case gloox::NonSaslNotAuthorized:
            text += "Incorrect credentials.";
            break;
        default:
            text += "Unknown error.";
        }
        break;
    case gloox::ConnUserDisconnected:
        // The user (or higher-level protocol) requested a disconnect.
        break;
    case gloox::ConnNotConnected:
        text = "There is no active connection.";
        break;
    default:
        text = "An unknown error occured.";
    }
    return text;
}/*}}}*/

// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
