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


#pragma once


#include <stdint.h>
#include <string>
#include <vector>
#include <set>
#include "Poco/DateTime.h"
#include "Poco/Nullable.h"
#include "ofx/Twitter/Types.h"
#include "ofx/Twitter/Entities.h"
#include "ofx/Twitter/Profile.h"
//#include "ofx/Twitter/Tweet.h"


namespace ofx {
namespace Twitter {


// https://dev.twitter.com/docs/platform-objects/users
class User: public BaseNamedUser
{
public:
    enum WithheldScope
    {
        USER,
        STATUS
    };

    User();
    
    User(int64_t ID,
         const std::string& screenName,
         const std::string& name);

    virtual ~User();

    bool areContributorsEnabled() const;
    const Poco::DateTime& getCreatedAt() const;
    bool hasDefaultProfile() const;
    bool hasDefaultProfileImage() const;
    const Poco::Nullable<std::string>& getDescription() const;
    const Entities& getEntities() const;
    int getFavouritesCount() const;
    const Poco::Nullable<bool>& wasFollowRequestSent() const;
    int getFollowersCount() const;
    int getFriendsCount() const;
    bool isGeoEnabled() const;
    bool isTranslator() const;
    const std::string& getLanguage() const;
    int getListedCount() const;
    const Poco::Nullable<std::string>& getLocation() const;
    const Profile& getProfile() const;
    bool isProtected() const;
    bool showsAllInlineMedia();
//    Poco::Nullable<Tweet> getStatus() const;
    int getStatusesCount() const;
    const Poco::Nullable<std::string>& getTimeZone() const;
    const Poco::Nullable<std::string>& getURL() const;
    const Poco::Nullable<int>& getUTCOffset() const;
    bool isVerified() const;
    const Contries& getWithheldInCountries() const;
    const WithheldScope& getWithheldScope() const;

private:
    bool _contributorsEnabled;
    Poco::DateTime _createdAt;
    bool _hasDefaultProfile;
    bool _hasDefaultProfileImage;

    Poco::Nullable<std::string> _description;
    Entities _entities;
    int _favouritesCount;
    Poco::Nullable<bool> _followRequestSent;
    int _followersCount;
    int _friendsCount;
    bool _isGeoEnabled;
    bool _isTranslator;
    std::string _language;
    int _listedCount;
    Poco::Nullable<std::string> _location;

    Profile _profile;

    bool _isProtected;

    bool _showsAllInlineMedia;

//    Poco::Nullable<Tweet> _status;
    int _statusesCount;

    Poco::Nullable<std::string> _timeZone;
    Poco::Nullable<std::string> _url;
    Poco::Nullable<int> _UTCOffset; // < 0 unset

    bool _isVerified;

    Contries _withheldInCountries;
    WithheldScope _withheldScope;

    friend class Deserializer;

};


} } // namespace ofx::Twitter
