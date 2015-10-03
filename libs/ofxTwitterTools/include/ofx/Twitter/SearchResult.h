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


#pragma once


#include <string>
#include "Poco/Net/NameValueCollection.h"
#include "ofx/Twitter/BaseTwitterResponse.h"
#include "ofx/Twitter/Tweet.h"
#include "ofx/Twitter/SearchQuery.h"


namespace ofx {
namespace Twitter {


/// \brief A Twitter Search Request.
///
/// \sa https://dev.twitter.com/rest/reference/get/search/tweets
class SearchResult: public BaseTwitterResponse
{
public:
    SearchResult();

    SearchResult(Poco::Net::HTTPResponse::HTTPStatus status);

    virtual ~SearchResult();

    const std::vector<Tweet>& tweets() const;

    std::size_t count() const;

    const std::string& query() const;

    int64_t maxId() const;

    int64_t sinceId() const;

    float completedIn() const;

    Poco::Nullable<SearchQuery> nextResult() const;

    Poco::Nullable<SearchQuery> refreshResults() const;

protected:
    std::vector<Tweet> _tweets;

    float _completedIn;

    int64_t _maxId;

    int64_t _sinceId;

    std::string _query;

    Poco::Nullable<SearchQuery> _nextResult;

    Poco::Nullable<SearchQuery> _refreshResult;

    friend class Deserializer;
};


} } // namespace ofx::Twitter
