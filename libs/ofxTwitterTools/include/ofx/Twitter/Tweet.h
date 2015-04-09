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
#include <map>
#include <vector>
#include "Poco/DateTime.h"
#include "Poco/Nullable.h"
#include "ofx/Geo/Coordinate.h"
#include "ofx/Twitter/Entities.h"
#include "ofx/Twitter/Types.h"
#include "ofx/Twitter/Places.h"
#include "ofx/Twitter/User.h"


namespace ofx {
namespace Twitter {


//  https://dev.twitter.com/docs/platform-objects/tweets
class Tweet
{
public:
    Tweet();
    
    virtual ~Tweet();

    const Annotations& annotations() const;

    Poco::Nullable<Contributors> contributors() const;

    Poco::Nullable<Geo::Coordinate> coordinates() const;

    int64_t id() const;

    Poco::DateTime createdAt() const;

    Poco::Nullable<User> user() const;

    const std::string& text() const;

private:

    Annotations _annotations; // unused

    Poco::Nullable<Contributors> _contributors;

    Poco::Nullable<Geo::Coordinate> _coordinates;

    Poco::DateTime _createdAt;

    int64_t _utcOffset;

    Poco::Nullable<int64_t> _currentUserRetweet;

    Entities _entities;

    Poco::Nullable<int64_t> _favoriteCount;

    Poco::Nullable<bool> _favorited;

    std::string _filterLevel;

    int64_t _id;

    Poco::Nullable<std::string> _inReplyToScreenName;
    Poco::Nullable<int64_t> _inReplyToStatusId;
    Poco::Nullable<int64_t> _inReplyToUserId;
    Poco::Nullable<std::string> _lang;
    Poco::Nullable<bool> _possiblySensitive;
    // Scopes _scopes;

    int64_t _retweetCount;

    Poco::Nullable<bool> _retweeted;

//    Poco::Nullable<Tweet> _retweetedStatus;
    std::string _source;
    std::string _text;

    bool _truncated;

    Poco::Nullable<User> _user;

    bool _withheldCopyright;

    Poco::Nullable<Places> _places;

    friend class Deserializer;

};


} } // namespace ofx::Twitter
