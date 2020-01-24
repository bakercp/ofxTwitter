//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/Twitter/Status.h"
#include "ofx/Twitter/BaseUser.h"
#include "ofx/Twitter/Entities.h"
#include "ofx/Twitter/User.h"
#include "ofx/Twitter/Utils.h"
#include "ofLog.h"


// Undefine Status from Xlib.h.
#ifdef Status
#undef Status
#endif


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


std::string Status::url() const
{
    return "https://twitter.com/openframeworks/status" + std::to_string(id());
}


int64_t Status::id() const
{
    return _id;
}


const User* Status::user() const
{
    return _user.get();
}


std::string Status::language() const
{
    return _language;
}


Status::Annotations Status::annotations() const
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


Poco::DateTime Status::createdAt() const
{
    return _createdAt;
}


int64_t Status::utcOffset() const
{
    return _utcOffset;
}


int64_t Status::currentUserRetweet() const
{
    return _currentUserRetweet;
}


Entities Status::entities() const
{
    return _entities;
}


Entities Status::extendedEntities() const
{
    return _extendedEntities;
}


const Status* Status::extendedTweet() const
{
    return _extendedTweet.get();
}


int64_t Status::favoriteCount() const
{
    return _favoriteCount;
}

    
int64_t Status::quoteCount() const
{
    return _quoteCount;
}


int64_t Status::replyCount() const
{
    return _replyCount;
}


bool Status::isQuoteStatus() const
{
    return _isQuoteStatus;
}


int64_t Status::quotedStatusId() const
{
    return _quotedStatusId;
}


const Status* Status::quotedStatus() const
{
    return _quotedStatus.get();
}

    
const QuotedStatusPermalink* Status::quotedStatusPermalink() const
{
    return _quotedStatusPermalink.get();
}
    

bool Status::favorited() const
{
    return _favorited;
}


Status::FilterLevel Status::filterLevel() const
{
    return _filterLevel;
}


std::string Status::inReplyToScreenName() const
{
    return _inReplyToScreenName;
}


int64_t Status::inReplyToStatusId() const
{
    return _inReplyToStatusId;
}


int64_t Status::inReplyToUserId() const
{
    return _inReplyToUserId;
}


bool Status::possiblySensitive() const
{
    return _possiblySensitive;
}


std::map<std::string, bool> Status::scopes() const
{
    return _scopes;
}


int64_t Status::retweetCount() const
{
    return _retweetCount;
}


bool Status::retweeted() const
{
    return _retweeted;
}


const Status* Status::retweetedStatus() const
{
    return _retweetedStatus.get();
}


std::string Status::source() const
{
    return _source;
}


std::string Status::text() const
{
    return _text;
}


std::string Status::fullText() const
{
    return _fullText;
}


std::string::size_type Status::displayTextStart() const
{
    return _displayTextStart;
}


std::string::size_type Status::displayTextEnd() const
{
    return _displayTextEnd;
}


std::string Status::displayText() const
{
    if (_displayTextStart < text().length() && _displayTextEnd < text().length())
    {
        return _text.substr(_displayTextStart, _displayTextEnd);
    }
    else
    {
        return _text;
    }
}

bool Status::truncated() const
{
    return _truncated;
}


bool Status::withheldCopyright() const
{
    return _withheldCopyright;
}


std::vector<std::string> Status::withheldInCountries() const
{
    return _withheldInCountries;
}


std::string Status::withheldScope() const
{
    return _withheldScope;
}


const Place* Status::place() const
{
    return _place.get();
}


Status::Metadata Status::metadata() const
{
    return _metadata;
}


uint64_t Status::timestamp() const
{
    return _timestamp;
}


ofJson Status::json() const
{
    return _json;
}


Status Status::fromJSON(const ofJson& json)
{
    Status status;
    status._json = json;

    auto iter = json.cbegin();
    while (iter != json.cend())
    {
        const auto& key = iter.key();
        const auto& value = iter.value();

        if (Utils::endsWith(key, "_str")) { /* skip */}
        else if (key == "delete") { std::cout << "delete" << std::endl; }
        else if (key == "timestamp_ms") status._timestamp = std::stoull(value.get<std::string>());
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
                for (auto c: value)
                {
                    if (c.is_number())
                    {
                        status._contributors.push_back(BaseNamedUser(c.get<int64_t>()));
                    }
                    else ofLogWarning("Status::fromJSON") << "Contributor " <<  c.dump(4);
                }
            }
        }
        else if (key == "coordinates")
        {
            if (!value.is_null())
            {
                auto _iter = value.cbegin();
                while (_iter != value.cend())
                {
                    const auto& _key = _iter.key();
                    const auto& _value = _iter.value();

                    if (_key == "coordinates")
                    {
                        if (value.size() == 2)
                        {
                            if (status._coordinates != nullptr)
                            {
                                ofLogWarning("Status::fromJSON") << "In Coordinates: Coordinates were already set.";
                            }

                            status._coordinates = std::make_shared<Geo::Coordinate>(_value[1], _value[0]);
                        }
                        else ofLogWarning("Status::fromJSON") << "Coordinates have " << value.size() << " and should have 2.";
                    }
                    else if (_key == "type")
                    {
                        if (_value != "Point")
                        {
                            ofLogWarning("Status::fromJSON") << "Unknown coordinate type: " << _value;
                        }
                    }
                    else ofLogWarning("Status::fromJSON") << "Unknown geo key: " << _key << " " << value.dump(4);

                    ++_iter;
                }
            }
        }
        else if (key == "geo")
        {
            // Deprecated, use coordinate instead.
            // https://dev.twitter.com/overview/api/tweets
        }
        else if (key == "place")
        {
            if (!value.is_null())
            {
                status._place = std::make_shared<Place>(Place::fromJSON(value));
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
        else if (key == "reply_count") status._replyCount = value;
        else if (key == "quote_count") status._quoteCount = value;
        else if (key == "is_quote_status") status._isQuoteStatus = value;
        else if (key == "lang") status._language = value;
        else if (key == "metadata") status._metadata = Metadata::fromJSON(value);
        else if (key == "scopes")
        {
            auto _iter = value.cbegin();
            while (_iter != value.cend())
            {
                status._scopes.insert(std::make_pair(_iter.key(), _iter.value()));
                ++_iter;
            }
        }
        else if (key == "withheld_in_countries")
        {
            for (auto v: value)
            {
                status._withheldInCountries.push_back(v);
            }
        }
        else if (key == "extended_tweet")
        {
            status._extendedTweet = std::make_shared<Status>(Status::fromJSON(value));
        }
        else if (key == "full_text")
        {
            status._fullText = value;
        }
        else if (key == "display_text_range")
        {
            status._displayTextStart = value[0];
            status._displayTextEnd = value[1];
        }
        else if (key == "created_at")
        {
            Poco::DateTime date;

            if (Utils::parse(value, date))
            {
                status._createdAt = date;
            }
        }
        else if (key == "quoted_status_permalink")
        {
            status._quotedStatusPermalink = std::make_shared<QuotedStatusPermalink>(QuotedStatusPermalink::fromJson(value));
        }
        else ofLogWarning("Status::fromJSON") << "Unknown key: " << key << std::endl << value.dump(4);

        ++iter;
    }

    return status;
}


} } // namespace ofx::Twitter
