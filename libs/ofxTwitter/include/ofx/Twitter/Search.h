//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include <string>
#include "ofx/HTTP/GetRequest.h"
#include "ofx/Twitter/Status.h"
#include "ofx/Twitter/BaseResponse.h"


namespace ofx {
namespace Twitter {


/// \brief A Twitter Search Request.
///
/// \sa https://dev.twitter.com/rest/reference/get/search/tweets
class SearchRequest: public HTTP::GetRequest
{
public:
    enum class ResultType
    {
        MIXED,
        RECENT,
        POPULAR
    };

    SearchRequest(const std::string& query);

    virtual ~SearchRequest();

    // required
    void setQuery(const std::string& query);

    // optional
    void setGeoCode(double latitude,
                    double longitude,
                    double radius,
                    const std::string& units);

    // 2 letter language code.
    // https://en.wikipedia.org/wiki/List_of_ISO_639-1_codes
    void setLanguage(const std::string& language);

    void setLocale(const std::string& locale);

    void setResultType(ResultType resultType);

    void setCount(int count);

    void setUntil(int year, int month, int day);

    void setSinceId(int64_t id);

    void setMaxId(int64_t id);

    void setIncludeEntities(bool includeEntities);

    static const std::string UNITS_MILES;
    static const std::string UNITS_KILOMETERS;
    static const std::string RESOURCE_URL;

};


class SearchMetadata
{
public:
    SearchMetadata();

    virtual ~SearchMetadata();

    std::size_t count() const;

    std::string query() const;

    int64_t maxId() const;

    int64_t sinceId() const;

    float completedIn() const;

    // std::unique_ptr<SearchRequest> nextResult() const;

    // std::unique_ptr<SearchRequest> refreshResults() const;

    static SearchMetadata fromJSON(const ofJson& json);

private:
    float _completedIn = -1;

    int64_t _count = -1;

    int64_t _maxId = -1;

    int64_t _sinceId = -1;

    std::string _query;

    std::string _nextResults;

    std::string _refreshURL;


};


/// \brief A Twitter Search Request.
///
/// \sa https://dev.twitter.com/rest/reference/get/search/tweets
class SearchResponse: public BaseResponse<SearchRequest>
{
public:
    using BaseResponse<SearchRequest>::BaseResponse;

    virtual ~SearchResponse();

    std::vector<Status> statuses() const;

    SearchMetadata metadata() const;


protected:
    virtual void parseJSON(const ofJson& json) override;

private:
    std::vector<Status> _statuses;

    SearchMetadata _metadata;

};





} } // namespace ofx::Twitter
