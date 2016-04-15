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


#include "ofx/Twitter/Search.h"
#include "ofx/Twitter/Status.h"
#include "ofx/Twitter/Utils.h"
#include <sstream>
#include "ofLog.h"


namespace ofx {
namespace Twitter {


const std::string SearchRequest::UNITS_MILES = "mi";
const std::string SearchRequest::UNITS_KILOMETERS = "km";
const std::string SearchRequest::RESOURCE_URL = "https://api.twitter.com/1.1/search/tweets.json";


SearchRequest::SearchRequest(const std::string& query):
    HTTP::GetRequest(RESOURCE_URL, Poco::Net::HTTPRequest::HTTP_1_1)
{
    setQuery(query);
}


SearchRequest::~SearchRequest()
{
}


void SearchRequest::setQuery(const std::string& query)
{
    setFormField("q", query);
}


void SearchRequest::setGeoCode(double latitude,
                               double longitude,
                               double radius,
                               const std::string& units)
{
    std::stringstream ss;
    ss << latitude << "," << longitude << "," << radius << units;
    setFormField("geocode", ss.str());
}


void SearchRequest::setLanguage(const std::string& language)
{
    setFormField("lang", language);
}


void SearchRequest::setLocale(const std::string& locale)
{
    setFormField("locale", locale);
}


void SearchRequest::setResultType(ResultType resultType)
{
    switch (resultType)
    {
        case ResultType::MIXED:
            setFormField("result_type", "mixed");
            return;
        case ResultType::RECENT:
            setFormField("result_type", "recent");
            return;
        case ResultType::POPULAR:
            setFormField("result_type", "popular");
            return;
    }
}


void SearchRequest::setCount(int count)
{
    if (count > 100)
    {
        ofLogWarning("SearchRequest::setCount") << "Counts greater than 100 are ignored by Twitter.";
    }

    setFormField("count", std::to_string(count));
}


void SearchRequest::setUntil(int year, int month, int day)
{
    std::stringstream ss;
    ss << year << "-" << month << "-" << day;
    setFormField("until", ss.str());
}

    
void SearchRequest::setSinceId(int64_t id)
{
    setFormField("since_id", std::to_string(id));
}


void SearchRequest::setMaxId(int64_t id)
{
    setFormField("max_id", std::to_string(id));
}


void SearchRequest::setIncludeEntities(bool includeEntities)
{
    setFormField("include_entities", includeEntities ? "true" : "false");
}


SearchMetadata::SearchMetadata()
{
}


SearchMetadata::~SearchMetadata()
{
}


std::size_t SearchMetadata::count() const
{
    return _count;
}


std::string SearchMetadata::query() const
{
    return _query;
}


int64_t SearchMetadata::maxId() const
{
    return _maxId;
}


int64_t SearchMetadata::sinceId() const
{
    return _sinceId;
}


float SearchMetadata::completedIn() const
{
    return _completedIn;
}


//std::unique_ptr<SearchRequest> SearchMetadata::nextResult() const
//{
//    return nullptr;
//}
//
//
//std::unique_ptr<SearchRequest> SearchMetadata::refreshResults() const
//{
//    return nullptr;
//}


SearchMetadata SearchMetadata::fromJSON(const ofJson& json)
{
    SearchMetadata metadata;

    auto iter = json.cbegin();
    while (iter != json.cend())
    {
        const auto& key = iter.key();
        const auto& value = iter.value();

        if (Utils::endsWith(key, "_str")) { /* skip */ }
        else if (key == "completed_in") metadata._completedIn = value;
        else if (key == "count") metadata._count = value;
        else if (key == "max_id") metadata._maxId = value;
        else if (key == "since_id") metadata._sinceId = value;
        else if (key == "query") metadata._query = value;
        else if (key == "refresh_url") metadata._refreshURL = value;
        else if (key == "next_results") metadata._nextResults = value;
        else ofLogWarning("SearchMetadata::fromJSON") << "Unknown key: " << key;

        ++iter;
    }

    return metadata;
}


SearchResponse::~SearchResponse()
{
}


std::vector<Status> SearchResponse::statuses() const
{
    return _statuses;
}


SearchMetadata SearchResponse::metadata() const
{
    return _metadata;
}


void SearchResponse::parseJSON(const ofJson& json)
{
    auto iter = json.cbegin();
    while (iter != json.cend())
    {
        const auto& key = iter.key();
        const auto& value = iter.value();

        if (key == "search_metadata") _metadata = SearchMetadata::fromJSON(value);
        else if (key == "statuses")
        {
            for (const auto& status: value)
            {
                _statuses.push_back(Status::fromJSON(status));
            }
        }
        else ofLogWarning("SearchResponse::parseJSON") << "Unknown key: " << key;

        ++iter;
    }
}


} } // namespace ofx::Twitter
