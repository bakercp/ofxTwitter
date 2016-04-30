// =============================================================================
//
// Copyright (c) 2009-2016 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


#pragma once


#include <string>
#include "Poco/DateTime.h"


namespace ofx {
namespace Twitter {


/// \brief A collection of Twitter utilities.
class Utils
{
public:
    /// \brief Determine if one string ends with a given suffix.
    /// \param str The string to check.
    /// \param suffix The suffix to match.
    /// \returns true if str ends with suffix.
    static bool endsWith(const std::string& str, const std::string &suffix);

    /// \brief Parse a Twitter date string.
    /// \param dateString The raw date string to parse.
    /// \param date The destination date.
    /// \returns true if parsing was successful.
    static bool parse(const std::string& dateString, Poco::DateTime& date);

    /// \brief The default Twitter date format.
    static const std::string TWITTER_DATE_FORMAT;

private:
    Utils() = delete;
    ~Utils() = delete;

};


} } // namespace ofx::Twitter
