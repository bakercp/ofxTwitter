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


#include "ofx/Twitter/TwitterUtils.h"
#include "Poco/DateTimeParser.h"
#include "Poco/Exception.h"
#include "ofLog.h"


namespace ofx {
namespace Twitter {


const std::string TwitterUtils::TWITTER_DATE_FORMAT = "%w %b %f %H:%M:%S %Z %Y";


bool TwitterUtils::endsWith(const std::string &str, const std::string &suffix)
{
    return str.size() >= suffix.size()
        && str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}


bool TwitterUtils::parse(const std::string& dateString, Poco::DateTime& date)
{
    try
    {
        int tzd;
        Poco::DateTimeParser::parse(TWITTER_DATE_FORMAT, dateString, date, tzd);
    }
    catch (const Poco::SyntaxException& exc)
    {
        ofLogError("TwitterUtils::parse") << "Unable to parse date time string: " << exc.displayText();
        return false;
    }
}


} } // namespace ofx::Twitter
