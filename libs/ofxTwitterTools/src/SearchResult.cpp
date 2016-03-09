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


#include "ofx/Twitter/SearchResult.h"
#include <sstream>


namespace ofx {
namespace Twitter {


SearchResult::SearchResult(): BaseTwitterResponse(Poco::Net::HTTPResponse::HTTP_OK)
{
}


SearchResult::SearchResult(Poco::Net::HTTPResponse::HTTPStatus status):
    BaseTwitterResponse(status)
{
}


SearchResult::~SearchResult()
{
}

    
const std::vector<Tweet>& SearchResult::tweets() const
{
    return _tweets;
}
    

std::size_t SearchResult::count() const
{
    return _tweets.size();
}


const std::string& SearchResult::query() const
{
    return _query;
}


int64_t SearchResult::maxId() const
{
    return _maxId;
}


int64_t SearchResult::sinceId() const
{
    return _sinceId;
}


float SearchResult::completedIn() const
{
    return _completedIn;
}


Poco::Nullable<SearchQuery> SearchResult::nextResult() const
{
    SearchQuery query;
    return query;
}


Poco::Nullable<SearchQuery> SearchResult::refreshResults() const
{
    SearchQuery query;
    return query;
}


} } // namespace ofx::Twitter
