// =============================================================================
//
// Copyright (c) 2009-2015 Christopher Baker <http://christopherbaker.net>
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


#include "ofx/Twitter/Update.h"
#include "ofLog.h"
#include <sstream>
#include "Poco/Net/HTTPRequest.h"


namespace ofx {
namespace Twitter {


const std::string UpdateRequest::RESOURCE_URL = "https://api.twitter.com/1.1/statuses/update.json";


UpdateRequest::UpdateRequest(const std::string& status):
    HTTP::PostRequest(RESOURCE_URL, HTTP_1_1)
{
    setFormField("status", status);
}


void UpdateRequest::setStatus(const std::string& status)
{
    setFormField("status", status);
}

//
//void SearchRequest::setGeoCode(double latitude,
//                               double longitude,
//                               double radius,
//                               RadiusUnits units)
//{
//    std::stringstream ss;
//
//    ss << latitude << "," << longitude << "," << radius;
//
//    switch (units)
//    {
//        case UNITS_KILOMETERS:
//            ss << "km";
//            break;
//        case UNITS_MILES:
//            ss << "mi";
//            break;
//    }
//
//    setFormField("geocode", ss.str());
//}
//
//
//void SearchRequest::setLanguage(const std::string& language)
//{
//    setFormField("lang", language);
//}
//
//
//void SearchRequest::setLocale(const std::string& locale)
//{
//    setFormField("locale", locale);
//}
//
//
//void SearchRequest::setResultType(ResultType resultType)
//{
//    switch (resultType)
//    {
//        case RESULT_MIXED:
//            set("result_type", "mixed");
//            return;
//        case RESULT_RECENT:
//            set("result_type", "recent");
//            return;
//        case RESULT_POPULAR:
//            set("result_type", "popular");
//            return;
//    }
//}
//
//
//void SearchRequest::setCount(int count)
//{
//    if (count > 100)
//    {
//        ofLogWarning("SearchRequest::setCount") << "Counts greater than 100 are ignored by Twitter.";
//    }
//
//    std::stringstream ss;
//    ss << count;
//    setFormField("count", ss.str());
//}
//
//
//void SearchRequest::setUntil(int year, int month, int day)
//{
//    std::stringstream ss;
//    ss << year << "-" << month << "-" << day;
//    setFormField("until", ss.str());
//}
//
//    
//void SearchRequest::setSinceID(int64_t id)
//{
//    std::stringstream ss;
//    ss << id;
//    setFormField("since_id", ss.str());
//}
//
//
//void SearchRequest::setMaxID(int64_t id)
//{
//    std::stringstream ss;
//    ss << id;
//    setFormField("max_id", ss.str());
//}
//
//
//void SearchRequest::setIncludeEntities(bool includeEntities)
//{
//    setFormField("include_entities", includeEntities ? "true" : "false");
//}


} } // namespace ofx::Twitter
