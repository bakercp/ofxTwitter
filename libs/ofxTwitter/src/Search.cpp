//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/Twitter/Search.h"
#include "ofx/Twitter/Status.h"
#include "ofx/Twitter/Utils.h"
#include <sstream>
#include "ofLog.h"


namespace ofx {
namespace Twitter {


const std::string SearchQuery::UNITS_MILES = "mi";
const std::string SearchQuery::UNITS_KILOMETERS = "km";
const std::string SearchQuery::RESOURCE_URL = "https://api.twitter.com/1.1/search/tweets.json";


SearchQuery::SearchQuery(const std::string& query)
{
    setQuery(query);
}


SearchQuery::~SearchQuery()
{
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
        case ResultType::MIXED:
            set("result_type", "mixed");
            return;
        case ResultType::RECENT:
            set("result_type", "recent");
            return;
        case ResultType::POPULAR:
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

    set("count", std::to_string(count));
}


void SearchQuery::setUntil(int year, int month, int day)
{
    std::stringstream ss;
    ss << year << "-" << month << "-" << day;
    set("until", ss.str());
}


void SearchQuery::setSinceId(int64_t id)
{
    set("since_id", std::to_string(id));
}


void SearchQuery::setMaxId(int64_t id)
{
    set("max_id", std::to_string(id));
}


void SearchQuery::setIncludeEntities(bool includeEntities)
{
    set("include_entities", includeEntities ? "true" : "false");
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


std::vector<Error> SearchResponse::errors() const
{
    return _errors;
}


SearchResponse SearchResponse::fromJSON(const ofJson& json)
{
    SearchResponse response;

    auto iter = json.cbegin();
    while (iter != json.cend())
    {
        const auto& key = iter.key();
        const auto& value = iter.value();

        if (key == "search_metadata")
        {
            response._metadata = SearchMetadata::fromJSON(value);
        }
        else if (key == "statuses")
        {
            for (const auto& status: value)
            {
                response._statuses.push_back(Status::fromJSON(status));
            }
        }
        else if (key == "errors")
        {
            for (const auto& error: value)
            {
                response._errors.push_back(Error::fromJSON(error));
            }
        }
        else ofLogWarning("SearchResponse::parseJSON") << "Unknown key: " << key;

        ++iter;
    }

    return response;
}


} } // namespace ofx::Twitter
