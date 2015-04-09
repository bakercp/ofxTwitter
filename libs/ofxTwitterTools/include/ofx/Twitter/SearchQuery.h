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


namespace ofx {
namespace Twitter {


/// \brief A Twitter Search Request.
///
/// \sa https://dev.twitter.com/rest/reference/get/search/tweets
class SearchQuery: public Poco::Net::NameValueCollection
{
public:
    enum ResultType
    {
        RESULT_TYPE_MIXED,
        RESULT_TYPE_RECENT,
        RESULT_TYPE_POPULAR
    };

    SearchQuery();

    SearchQuery(const std::string& query);

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

};


} } // namespace ofx::Twitter
