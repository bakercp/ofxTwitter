//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/Twitter/User.h"
#include "ofx/Twitter/Utils.h"
#include "ofx/Twitter/Status.h"
#include "ofLog.h"


// Undefine Status from Xlib.h.
#undef Status


namespace ofx {
namespace Twitter {



User::User()
{
}


User::User(int64_t id,
           const std::string& screenName,
           const std::string& name):
    BaseNamedUser(id, screenName, name)
{
}


User::~User()
{
}


bool User::contributorsEnabled() const
{
    return _contributorsEnabled;
}


Poco::DateTime User::createdAt() const
{
    return _createdAt;
}


bool User::defaultProfile() const
{
    return _defaultProfile;
}


bool User::defaultProfileImage() const
{
    return _defaultProfileImage;
}


std::string User::description() const
{
    return _description;
}


Entities User::entities() const
{
    return _entities;
}


int64_t User::favouritesCount() const
{
    return _favouritesCount;
}


bool User::wasFollowRequestSent() const
{
    return _followRequestSent;
}


int64_t User::followersCount() const
{
    return _followersCount;
}


int64_t User::friendsCount() const
{
    return _friendsCount;
}


bool User::isGeoEnabled() const
{
    return _isGeoEnabled;
}


bool User::isTranslator() const
{
    return _isTranslator;
}


std::string User::language() const
{
    return _language;
}


int64_t User::listedCount() const
{
    return _listedCount;
}


std::string User::location() const
{
    return _location;
}


Profile User::profile() const
{
    return _profile;
}


bool User::isProtected() const
{
    return _isProtected;
}


bool User::showsAllInlineMedia()
{
    return _showsAllInlineMedia;
}


const Status* User::status() const
{
    return _status.get();
}


int64_t User::statusesCount() const
{
    return _statusesCount;
}


const std::string* User::timeZone() const
{
    return _timeZone.get();
}


const std::string* User::url() const
{
    return _url.get();
}


const int64_t* User::utcOffset() const
{
    return _UTCOffset.get();
}


bool User::verified() const
{
    return _verified;
}


std::vector<std::string> User::withheldInCountries() const
{
    return _withheldInCountries;
}


User::WithheldScope User::withheldScope() const
{
    return _withheldScope;
}


std::string User::translatorType() const
{
    return _translatorType;
}


User User::fromJSON(const ofJson& json)
{
    User user;

    auto iter = json.cbegin();
    while (iter != json.cend())
    {
        const auto& key = iter.key();
        const auto& value = iter.value();


        if (Utils::endsWith(key, "_str")) { /* skip */}

        else if (key == "contributors_enabled") user._contributorsEnabled = value;
        else if (key == "created_at")
        {
            Poco::DateTime date;

            if (Utils::parse(value, date))
            {
                user._createdAt = date;
            }
        }
        else if (key == "default_profile") user._defaultProfile = value;
        else if (key == "default_profile_image") user._defaultProfileImage = value;
        else if (key == "description")
        {
            if (!value.is_null())
            {
                user._description = value;
            }
        }


        else if (key == "entities") user._entities = Entities::fromJSON(value);
        else if (key == "favourites_count") user._favouritesCount = value;
        else if (key == "follow_request_sent")
        {
            if (!value.is_null())
            {
                user._followRequestSent = value;
            }
        }

        else if (key == "followers_count") user._followersCount = value;
        else if (key == "following")
        {
            if (!value.is_null())
            {
                user._following = value;
            }
        }
        else if (key == "friends_count") user._friendsCount = value;
        else if (key == "geo_enabled") user._geoEnabled = value;
        else if (key == "has_extended_profile") user._hasExtendedProfile = value;
        else if (key == "id") user._id = value;
        else if (key == "is_translation_enabled") user._isTranslationEnabled = value;
        else if (key == "is_translator") user._geoEnabled = value;
        else if (key == "lang") user._language = value;
        else if (key == "listed_count") user._listedCount = value;
        else if (key == "location")
        {
            if (!value.is_null())
            {
                user._location = value;
            }
        }
        else if (key == "name") user._name = value;
        else if (key == "notifications")
        {
            if (!value.is_null())
            {
                user._notifications = value;
            }
        }
        else if (key == "profile_background_color") user._profile.setBackgroundColorHex(value);
        else if (key == "profile_background_image_url") { /* TODO */ }
        else if (key == "profile_background_image_url_https") { /* TODO */ }
        else if (key == "profile_background_tile") { /* TODO */ }
        else if (key == "profile_banner_url") { /* TODO */ }
        else if (key == "profile_image_url") { /* TODO */ }
        else if (key == "profile_image_url_https") { /* TODO */ }
        else if (key == "profile_link_color") { /* TODO */ }
        else if (key == "profile_sidebar_border_color") { /* TODO */ }
        else if (key == "profile_sidebar_fill_color") { /* TODO */ }
        else if (key == "profile_text_color") { /* TODO */ }
        else if (key == "profile_use_background_image") { /* TODO */ }
        else if (key == "protected") user._protected = value;
        else if (key == "screen_name") user._screenName = value;
        else if (key == "statuses_count") user._statusesCount = value;
        else if (key == "translator_type") user._translatorType = value;
        else if (key == "time_zone")
        {
            if (!value.is_null())
            {
                user._timeZone = std::make_shared<std::string>(value.get<std::string>());
            }
        }
        else if (key == "url")
        {
            if (!value.is_null())
            {
                user._url = std::make_shared<std::string>(value.get<std::string>());
            }
        }
        else if (key == "utc_offset")
        {
            if (!value.is_null())
            {
                user._UTCOffset = std::make_shared<int64_t>(value);
            }
        }
        else if (key == "verified") user._verified = value;
        else
        {
            ofLogWarning("User::fromJSON") << "Unknown key: " << key;

            std::cout << value.dump(4) << std::endl;
        }
        ++iter;
    }

    return user;
}


} } // namespace ofx::Twitter
