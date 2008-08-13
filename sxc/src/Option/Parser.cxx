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
#include <vector>
#include <iostream>

#include <Option/Parser.hxx>
#include <Exception/OptionException.hxx>

/*}}}*/

namespace Option
{
    void Parser::addOption(OptionBase *option)/*{{{*/
    {
        // The options having a name have to be parsed first. After
        // that all the nameless options can be passed. Therefore the
        // nameless are appended to an own vector.
        if (option->getLongName() == ""
        && option->getShortName() == ' ') {
            _namelessOptions.push_back(option);
        } else {
            // Check for conflict before adding.
            for(
            std::vector<OptionBase *>::iterator availOption = _options.begin();
            availOption != _options.end();
            ++availOption) {
                if ((*availOption)->getShortName() == option->getShortName())
                    throw Exception::OptionException(
                        Exception::OptionsConflicting,
                        "-" + option->getShortName());
                if ((*availOption)->getLongName() == option->getLongName())
                    throw Exception::OptionException(
                        Exception::OptionsConflicting,
                        "--" + option->getLongName());
            }

            _options.push_back(option);
        }
    }/*}}}*/

    void Parser::parse(char *argv[])/*{{{*/
    {
        _programName = argv[0];

        std::vector<std::string> arguments;

        for (int i = 1; argv[i]; ++i)
            arguments.push_back(argv[i]);

        // Parse normal options./*{{{*/

        // Walk through every option and check it for every argument
        // supplied. If something was found, remove it from the
        // arguments vector.
        for (
        std::vector<OptionBase *>::iterator option = _options.begin();
        option != _options.end();
        ++option) {
            for (
            std::vector<std::string>::iterator argument = arguments.begin();
            argument != arguments.end();) {
                if ("--help" == *argument || "-h" == *argument) {
                    throw Exception::OptionException(Exception::ShowUsage);
                } if ("--" + (*option)->getLongName() == *argument
                || std::string("-") + (*option)->getShortName() == *argument) {
                    if ((*option)->getRequiresArgument()) {
                        if (argument + 1 == arguments.end())
                            throw Exception::OptionException(
                                Exception::ValueNotSet,
                                (*option)->getName());
                        // Get the next argument.
                        argument = arguments.erase(argument);
                        (*option)->setValue(*argument);
                    } else {
                        (*option)->setValue("");
                    }
                    argument = arguments.erase(argument);
                } else {
                    // An argument with multiple options set. (-ab for
                    // example to set -a and -b)
                    while (argument->length() > 1
                    && argument->at(0) == '-'
                    && argument->at(1) != '-'
                    && argument->find((*option)->getShortName())
                       != std::string::npos) {
                        (*option)->setValue("");
                        // Delete the character.
                        argument->erase(argument->begin()
                        + argument->find(((*option)->getShortName())));
                    }
                    ++argument;
                }
            }

            if ((*option)->getIsObligatory() && !(*option)->getIsSet()) {
                throw Exception::OptionException(
                    Exception::OptionNotSet,
                    (*option)->getName());
            }
        }/*}}}*/

        // Parse nameless options./*{{{*/
        for (
        std::vector<OptionBase *>::iterator option = _namelessOptions.begin();
        option != _namelessOptions.end();
        ++option) {
            for (
            std::vector<std::string>::iterator argument = arguments.begin();
            argument != arguments.end() && !(*option)->getIsSet();) {
                if (argument->at(0) != '-') {
                    (*option)->setValue(*argument);
                    argument = arguments.erase(argument);
                } else {
                    ++argument; // Throwing later when checking the size.
                }
            }

            if ((*option)->getIsObligatory() && !(*option)->getIsSet())
                throw Exception::OptionException(
                    Exception::OptionNotSet,
                    (*option)->getName());
        }/*}}}*/

        if (arguments.size())
            throw Exception::OptionException(
                Exception::OptionUnknown,
                arguments.at(0));
    }/*}}}*/

    void Parser::showUsage()/*{{{*/
    {
        std::vector<std::string> out;

        out.push_back("Usage: " + _programName);

        // Handle normal options./*{{{*/
        for (
        std::vector<OptionBase *>::iterator option = _options.begin();
        option != _options.end();
        ++option) {
            out.front() += getUsageShort(**option);
            out.push_back(getUsageLine(**option));
        }/*}}}*/

        // Handle nameless options./*{{{*/
        for (
        std::vector<OptionBase *>::iterator option = _namelessOptions.begin();
        option != _namelessOptions.end();
        ++option) {
            out.front() += getUsageShort(**option);
            out.push_back(getUsageLine(**option));
        }/*}}}*/

        // Output lines./*{{{*/
        for (
        std::vector<std::string>::iterator line = out.begin();
        line != out.end();
        ++line) {
            std::cerr << *line << std::endl;
        }/*}}}*/
    }/*}}}*/

    std::string Parser::getUsageShort(OptionBase option)/*{{{*/
    {
        std::string text;

        if (option.getShortName() != ' ') {
            text = std::string("-") + option.getShortName();
        } else if (option.getLongName() != "") {
            text = std::string("--") + option.getLongName();
        }
        if (option.getRequiresArgument())
            text += " " + option.getVariable();
        if (!option.getIsObligatory()) {
            text = " [" + text + "]";
        } else if (option.getShortName() != ' ' || option.getLongName() != "") {
            text = " " + text;
        }

        return text;
    }/*}}}*/

    std::string Parser::getUsageLine(OptionBase option)/*{{{*/
    {
        std::string line;

        if (option.getShortName() != ' ') {
            line += std::string("-") + option.getShortName();
            if (option.getLongName() != "")
                line += "/";
        }
        if (option.getLongName() != "")
            line += std::string("--") + option.getLongName();
        if (option.getLongName() != "" || option.getShortName() != ' ')
            line += std::string(" ");
        line += option.getVariable() + ": " + option.getDescription();

        return line;
    }/*}}}*/
}
// Use no tabs at all; four spaces indentation; max. eighty chars per line.
// vim: et ts=4 sw=4 tw=80 fo+=c fdm=marker
