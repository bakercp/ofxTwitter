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


int64_t User::followersCount() const
{
    return _followersCount;
}


int64_t User::friendsCount() const
{
    return _friendsCount;
}


int64_t User::listedCount() const
{
    return _listedCount;
}


std::string User::location() const
{
    return _location;
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


std::string User::url() const
{
    return _url;
}


std::string User::profileImageUrlHttps() const
{
    return _profileImageUrlHttps;
}


bool User::isVerified() const
{
    return _isVerified;
}


std::vector<std::string> User::withheldInCountries() const
{
    return _withheldInCountries;
}


User::WithheldScope User::withheldScope() const
{
    return _withheldScope;
}


User User::fromJSON(const ofJson& json)
{
    User user;

    auto iter = json.cbegin();
    while (iter != json.cend())
    {
        const auto& key = iter.key();
        const auto& value = iter.value();

        if (key == "created_at")
        {
            Poco::DateTime date;
            if (Utils::parse(value, date)) user._createdAt = date;
        }
        else if (key == "default_profile") user._defaultProfile = value;
        else if (key == "default_profile_image") user._defaultProfileImage = value;
        else if (key == "description") { if (!value.is_null()) user._description = value; }
        else if (key == "favourites_count") user._favouritesCount = value;
        else if (key == "followers_count") user._followersCount = value;
        else if (key == "friends_count") user._friendsCount = value;
        else if (key == "id") user._id = value;
        else if (key == "listed_count") user._listedCount = value;
        else if (key == "location") { if (!value.is_null()) user._location = value; }
        else if (key == "name") user._name = value;
        else if (key == "protected") user._protected = value;
        else if (key == "screen_name") user._screenName = value;
        else if (key == "statuses_count") user._statusesCount = value;
        else if (key == "url") { if (!value.is_null()) user._url = value; }
        else if (key == "verified") user._isVerified = value;
        else if (key == "profile_image_url_https") { user._profileImageUrlHttps = value; }
        else if (key == "profile_banner_url") { user._profileBannerUrl; }

        // Undocumented
        else if (key == "entities") user._entities = Entities::fromJSON(value);

        // To skip.
        else if (Utils::endsWith(key, "_str")) { /* skip */}

        // Deprecated
        else if (key == "utc_offset") { /* deprecated */ }
        else if (key == "time_zone")  { /* deprecated */ }
        else if (key == "lang") { /* deprecated */ }
        else if (key == "geo_enabled") { /* deprecated */ }
        else if (key == "following") { /* deprecated */ }
        else if (key == "follow_request_sent") { /* deprecated */ }
        else if (key == "has_extended_profile") { /* deprecated */ }
        else if (key == "notifications") { /* deprecated */ }
        else if (key == "contributors_enabled")  { /* deprecated */ }

        else if (key == "profile_image_url") { /* deprecated */ }
        else if (key == "profile_background_color") { /* deprecated */ }
        else if (key == "profile_background_image_url") { /* deprecated */ }
        else if (key == "profile_background_image_url_https") { /* deprecated */ }
        else if (key == "profile_background_tile") { /* deprecated */ }
        else if (key == "profile_link_color") { /* deprecated */ }
        else if (key == "profile_sidebar_border_color") { /* deprecated */ }
        else if (key == "profile_sidebar_fill_color") { /* deprecated */ }
        else if (key == "profile_text_color") { /* deprecated */ }
        else if (key == "profile_use_background_image") { /* deprecated */ }
        else if (key == "is_translator") { /* deprecated */ }
        else if (key == "is_translation_enabled") { /* deprecated */ }
        else if (key == "translator_type") { /* deprecated */ }

        else
        {
            ofLogWarning("User::fromJSON") << "Unknown key: " << key;
            ofLogWarning("User::fromJSON") << "Value: " << std::endl << value.dump(4);
        }
        ++iter;
    }

    return user;
}


} } // namespace ofx::Twitter
