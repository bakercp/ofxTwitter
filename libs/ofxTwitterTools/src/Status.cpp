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


#include "ofx/Twitter/Status.h"
#include "ofx/Twitter/Utils.h"
#include "ofx/Twitter/BaseUser.h"
#include "ofx/Twitter/User.h"
#include "ofLog.h"


namespace ofx {
namespace Twitter {


std::string Status::Metadata::isoLanguageCode() const
{
    return _isoLanguageCode;
}


std::string Status::Metadata::resultType() const
{
    return _resultType;
}


Status::Metadata Status::Metadata::fromJSON(const ofJson& json)
{
    Metadata metadata;

    auto iter = json.cbegin();
    while (iter != json.cend())
    {
        const auto& key = iter.key();
        const auto& value = iter.value();

        if (Utils::endsWith(key, "_str")) { /* skip */}
        else if (key == "iso_language_code") metadata._isoLanguageCode = value;
        else if (key == "result_type") metadata._resultType = value;
        else {
            ofLogWarning("Status::Metadata::fromJSON") << "Unknown key: " << key;
            std::cout << value.dump(4) << std::endl;
        }
        ++iter;
    }
    
    return metadata;
}


Status::Status()
{
}


Status::~Status()
{
}


std::map<std::string, std::string> Status::annotations() const
{
    return _annotations;
}


std::vector<BaseNamedUser> Status::contributors() const
{
    return _contributors;
}


const Geo::Coordinate* Status::coordinates() const
{
    return _coordinates.get();
}


int64_t Status::id() const
{
    return _id;
}


Poco::DateTime Status::createdAt() const
{
    return _createdAt;
}


const User* Status::user() const
{
    return _user.get();
}


std::string Status::text() const
{
    return _text;
}


Status Status::fromJSON(const ofJson& json)
{
    Status status;

    auto iter = json.cbegin();
    while (iter != json.cend())
    {
        const auto& key = iter.key();
        const auto& value = iter.value();

        if (Utils::endsWith(key, "_str")) { /* skip */}
        else if (key == "id") status._id = value;

        else if (key == "filter_level")
        {
            if (value == "none") status._filterLevel = FilterLevel::NONE;
            else if (value == "low") status._filterLevel = FilterLevel::LOW;
            else if (value == "medium") status._filterLevel = FilterLevel::LOW;
            else ofLogError("Status::fromJSON") << "Unknown filter level: " << value;
        }
        else if (key == "in_reply_to_screen_name")
        {
            if (!value.is_null()) status._inReplyToScreenName = value;
        }
        else if (key == "in_reply_to_status_id")
        {
            if (!value.is_null()) status._inReplyToStatusId = value;
        }
        else if (key == "in_reply_to_user_id")
        {
            if (!value.is_null()) status._inReplyToUserId = value;
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
                status._user = std::make_shared<User>(User::fromJSON(value));
            }
        }
        else if (key == "retweeted_status")
        {
            if (!value.is_null())
            {
                status._retweetedStatus = std::make_shared<Status>(Status::fromJSON(value));
            }
        }
        else if (key == "quoted_status_id") status._quotedStatusId = value;
        else if (key == "quoted_status")
        {
            if (!value.is_null())
            {
                status._quotedStatus = std::make_shared<Status>(Status::fromJSON(value));
            }
        }
        else if (key == "favorited") status._favorited = value;
        else if (key == "entities") status._entities = Entities::fromJSON(value);
        else if (key == "extended_entities") status._extendedEntities = Entities::fromJSON(value);
        else if (key == "text") status._text = value;
        else if (key == "possibly_sensitive") status._possiblySensitive = value;
        else if (key == "retweet_count") status._retweetCount = value;
        else if (key == "retweeted") status._retweeted = value;
        else if (key == "source") status._source = value;
        else if (key == "truncated") status._truncated = value;
        else if (key == "utc_offset") status._utcOffset = value;
        else if (key == "favorite_count") status._favoriteCount = value;
        else if (key == "is_quote_status") status._isQuoteStatus = value;
        else if (key == "lang") status._lang = value;
        else if (key == "metadata") status._metadata = Metadata::fromJSON(value);
        else if (key == "created_at")
        {
            Poco::DateTime date;

            if (Utils::parse(value, date))
            {
                status._createdAt = date;
            }
        }
        else ofLogWarning("Status::fromJSON") << "Unknown key: " << key << std::endl << value.dump(4);

        ++iter;
    }

    return status;
}


} } // namespace ofx::Twitter
