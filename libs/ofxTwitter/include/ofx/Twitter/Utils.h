//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


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

	/// \brief convert a DateTime object into a string.
    /// \param date The DateTime object to format.
    /// \param fmt The formating string.
    /// \returns formated string representing the DataTime object
	static std::string format(const Poco::DateTime& date, const std::string& fmt);
	
    /// \brief The default Twitter date format.
    static const std::string TWITTER_DATE_FORMAT;

private:
    Utils() = delete;
    ~Utils() = delete;

};


} } // namespace ofx::Twitter
