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


#include "ofx/Twitter/SearchQuery.h"
#include <sstream>
#include "ofLog.h"


namespace ofx {
namespace Twitter {


const std::string SearchQuery::UNITS_MILES = "mi";
const std::string SearchQuery::UNITS_KILOMETERS = "km";


SearchQuery::SearchQuery()
{
}


SearchQuery::SearchQuery(const std::string& query)
{
    set("q", query);
}


void SearchQuery::setQuery(const std::string& query)
{
    set("q", query);
}


void SearchQuery::setGeoCode(double latitude,
                             double longitude,
                             double radius,
                             const std::string& units)
{
    std::stringstream ss;
    ss << latitude << "," << longitude << "," << radius << units;
    set("geocode", ss.str());
}


void SearchQuery::setLanguage(const std::string& language)
{
    set("lang", language);
}


void SearchQuery::setLocale(const std::string& locale)
{
    set("locale", locale);
}


void SearchQuery::setResultType(ResultType resultType)
{
    switch (resultType)
    {
        case RESULT_TYPE_MIXED:
            set("result_type", "mixed");
            return;
        case RESULT_TYPE_RECENT:
            set("result_type", "recent");
            return;
        case RESULT_TYPE_POPULAR:
            set("result_type", "popular");
            return;
    }
}


void SearchQuery::setCount(int count)
{
    if (count > 100)
    {
        ofLogWarning("SearchRequest::setCount") << "Counts greater than 100 are ignored by Twitter.";
    }

    std::stringstream ss;
    ss << count;
    set("count", ss.str());
}


void SearchQuery::setUntil(int year, int month, int day)
{
    std::stringstream ss;
    ss << year << "-" << month << "-" << day;
    set("until", ss.str());
}

    
void SearchQuery::setSinceId(int64_t id)
{
    std::stringstream ss;
    ss << id;
    set("since_id", ss.str());
}


void SearchQuery::setMaxId(int64_t id)
{
    std::stringstream ss;
    ss << id;
    set("max_id", ss.str());
}


void SearchQuery::setIncludeEntities(bool includeEntities)
{
    set("include_entities", includeEntities ? "true" : "false");
}


} } // namespace ofx::Twitter
