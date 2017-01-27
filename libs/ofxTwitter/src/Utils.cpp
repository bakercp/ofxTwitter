//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/Twitter/Utils.h"
#include "Poco/DateTimeParser.h"
#include "Poco/Exception.h"
#include "ofLog.h"


namespace ofx {
namespace Twitter {


const std::string Utils::TWITTER_DATE_FORMAT = "%w %b %f %H:%M:%S %Z %Y";


bool Utils::endsWith(const std::string &str, const std::string &suffix)
{
    return str.size() >= suffix.size()
        && str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}


bool Utils::parse(const std::string& dateString, Poco::DateTime& date)
{
    try
    {
        int tzd;
        Poco::DateTimeParser::parse(TWITTER_DATE_FORMAT, dateString, date, tzd);
        return true;
    }
    catch (const Poco::SyntaxException& exc)
    {
        ofLogError("Utils::parse") << "Unable to parse date time string: " << exc.displayText();
        return false;
    }
}


} } // namespace ofx::Twitter
