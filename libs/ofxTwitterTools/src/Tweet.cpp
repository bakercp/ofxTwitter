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


#include "ofx/Twitter/Tweet.h"
#include "ofx/Twitter/TwitterUtils.h"
#include "ofLog.h"


namespace ofx {
namespace Twitter {


std::string Tweet::Metadata::isoLanguageCode() const
{
    return _isoLanguageCode;
}


std::string Tweet::Metadata::resultType() const
{
    return _resultType;
}


Tweet::Metadata Tweet::Metadata::fromJSON(const ofJson& json)
{
    Metadata metadata;

    auto iter = json.cbegin();
    while (iter != json.cend())
    {
        const auto& key = iter.key();
        const auto& value = iter.value();

        if (TwitterUtils::endsWith(key, "_str")) { /* skip */}
        else if (key == "iso_language_code") metadata._isoLanguageCode = value;
        else if (key == "result_type") metadata._resultType = value;
        else {
            ofLogWarning("Tweet::Metadata::fromJSON") << "Unknown key: " << key;
            std::cout << value.dump(4) << std::endl;
        }
        ++iter;
    }
    
    return metadata;
}


Tweet::Tweet()
{
}


Tweet::~Tweet()
{
}


Annotations Tweet::annotations() const
{
    return _annotations;
}


Contributors Tweet::contributors() const
{
    return _contributors;
}


const Geo::Coordinate* Tweet::coordinates() const
{
    return _coordinates.get();
}


int64_t Tweet::id() const
{
    return _id;
}


Poco::DateTime Tweet::createdAt() const
{
    return _createdAt;
}


const User* Tweet::user() const
{
    return _user.get();
}


std::string Tweet::text() const
{
    return _text;
}


Tweet Tweet::fromJSON(const ofJson& json)
{
    Tweet tweet;

    auto iter = json.cbegin();
    while (iter != json.cend())
    {
        const auto& key = iter.key();
        const auto& value = iter.value();

        if (TwitterUtils::endsWith(key, "_str")) { /* skip */}
        else if (key == "id") tweet._id = value;
        else if (key == "in_reply_to_screen_name")
        {
            if (!value.is_null()) tweet._inReplyToScreenName = value;
        }
        else if (key == "in_reply_to_status_id")
        {
            if (!value.is_null()) tweet._inReplyToStatusId = value;
        }
        else if (key == "in_reply_to_user_id")
        {
            if (!value.is_null()) tweet._inReplyToUserId = value;
        }
        else if (key == "contributors")
        {
            if (!value.is_null())
            {
                std::cout << key << " " << value.dump(4) << std::endl;
            }
        }
        else if (key == "coordinates")
        {
            if (!value.is_null())
            {
                std::cout << key << " " << value.dump(4) << std::endl;
            }
        }
        else if (key == "geo")
        {
            if (!value.is_null())
            {
                std::cout << key << " " << value.dump(4) << std::endl;
            }
        }
        else if (key == "place")
        {
            if (!value.is_null())
            {
                std::cout << key << " " << value.dump(4) << std::endl;
            }
        }
        else if (key == "user")
        {
            if (!value.is_null())
            {
                tweet._user = std::make_shared<User>(User::fromJSON(value));
            }
        }
        else if (key == "retweeted_status")
        {
            if (!value.is_null())
            {
                tweet._retweetedStatus = std::make_shared<Tweet>(Tweet::fromJSON(value));
            }
        }
        else if (key == "quoted_status_id") tweet._quotedStatusId = value;
        else if (key == "quoted_status")
        {
            if (!value.is_null())
            {
                tweet._quotedStatus = std::make_shared<Tweet>(Tweet::fromJSON(value));
            }
        }
        else if (key == "favorited") tweet._favorited = value;
        else if (key == "entities") tweet._entities = Entities::fromJSON(value);
        else if (key == "text") tweet._text = value;
        else if (key == "possibly_sensitive") tweet._possiblySensitive = value;
        else if (key == "retweet_count") tweet._retweetCount = value;
        else if (key == "retweeted") tweet._retweeted = value;
        else if (key == "source") tweet._source = value;
        else if (key == "truncated") tweet._truncated = value;
        else if (key == "utc_offset") tweet._utcOffset = value;
        else if (key == "favorite_count") tweet._favoriteCount = value;
        else if (key == "is_quote_status") tweet._isQuoteStatus = value;
        else if (key == "lang") tweet._lang = value;
        else if (key == "metadata") tweet._metadata = Metadata::fromJSON(value);
        else if (key == "created_at")
        {
            Poco::DateTime date;

            if (TwitterUtils::parse(value, date))
            {
                tweet._createdAt = date;
            }
        }
        else {
            ofLogWarning("Tweet::fromJSON") << "Unknown key: " << key;

            std::cout << value.dump(4) << std::endl;
        }
        ++iter;
    }

    return tweet;
}


} } // namespace ofx::Twitter
