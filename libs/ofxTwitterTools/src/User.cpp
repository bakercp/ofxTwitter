// =============================================================================
//
// Copyright (c) 2009-2013 Christopher Baker <http://christopherbaker.net>
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


#include "ofx/Twitter/User.h"


namespace ofx {
namespace Twitter {

User::User():
    BaseNamedUser(),
    _contributorsEnabled(false),
    _createdAt(Poco::DateTime()),
    _hasDefaultProfile(false),
    _hasDefaultProfileImage(false),
    _description(Poco::Nullable<std::string>()),
    _entities(Entities()),
    _favouritesCount(0),
    _followRequestSent(Poco::Nullable<bool>()),
    _followersCount(0),
    _friendsCount(0),
    _isGeoEnabled(false),
    _isTranslator(false),
    _language("en"),
    _listedCount(0),
    _location(Poco::Nullable<std::string>()),
    _profile(Profile()),
    _isProtected(false),
    _showsAllInlineMedia(false),
//    _status(Poco::Nullable<Tweet>()),
    _statusesCount(0),
    _timeZone(Poco::Nullable<std::string>()),
    _url(Poco::Nullable<std::string>()),
    _utcOffset(Poco::Nullable<int>()),
    _isVerified(false),
    _withheldInCountries(Contries()),
    _withheldScope(USER)
{
}

User::User(int64_t ID,
           const std::string& screenName,
           const std::string& name):
    BaseNamedUser(ID, screenName, name),
    _contributorsEnabled(false),
    _createdAt(Poco::DateTime()),
    _hasDefaultProfile(false),
    _hasDefaultProfileImage(false),
    _description(Poco::Nullable<std::string>()),
    _entities(Entities()),
    _favouritesCount(0),
    _followRequestSent(Poco::Nullable<bool>()),
    _followersCount(0),
    _friendsCount(0),
    _isGeoEnabled(false),
    _isTranslator(false),
    _language("en"),
    _listedCount(0),
    _location(Poco::Nullable<std::string>()),
    _profile(Profile()),
    _isProtected(false),
    _showsAllInlineMedia(false),
//    _status(Poco::Nullable<Tweet>()),
    _statusesCount(0),
    _timeZone(Poco::Nullable<std::string>()),
    _url(Poco::Nullable<std::string>()),
    _utcOffset(Poco::Nullable<int>()),
    _isVerified(false),
    _withheldInCountries(Contries()),
    _withheldScope(USER)
{
}

User::~User()
{
}

bool User::areContributorsEnabled() const
{
    return _contributorsEnabled;
}

Poco::DateTime User::getCreatedAt() const
{
    return _createdAt;
}

bool User::hasDefaultProfile() const
{
    return _hasDefaultProfile;
}

bool User::hasDefaultProfileImage() const
{
    return _hasDefaultProfileImage;
}

Poco::Nullable<std::string> User::getDescription() const
{
    return _description;
}

Entities User::getEntities() const
{
    return _entities;
}

int User::getFavouritesCount() const
{
    return _favouritesCount;
}

Poco::Nullable<bool> User::wasFollowRequestSent() const
{
    return _followRequestSent;
}

int User::getFollowersCount() const
{
    return _followersCount;
}

int User::getFriendsCount() const
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

std::string User::getLanguage() const
{
    return _language;
}

int User::getListedCount() const
{
    return _listedCount;
}

Poco::Nullable<std::string> User::getLocation() const
{
    return _location;
}

Profile User::getProfile() const
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

//Poco::Nullable<Tweet> User::getStatus() const
//{
//    return _status;
//}

int User::getStatusesCount() const
{
    return _statusesCount;
}

Poco::Nullable<std::string> User::getTimeZone() const
{
    return _timeZone;
}

Poco::Nullable<std::string> User::getURL() const
{
    return _url;
}

Poco::Nullable<int> User::getUtcOffet() const
{
    return _utcOffset;
}

bool User::isVerified() const
{
    return _isVerified;
}

Contries User::getWithheldInCountries() const
{
    return _withheldInCountries;
}

User::WithheldScope User::getWithheldScope() const
{
    return _withheldScope;
}


} } // namespace ofx::Twitter
