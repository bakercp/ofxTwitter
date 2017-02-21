//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include <string>
#include <vector>
#include <set>
#include "Poco/DateTime.h"
#include "ofx/Twitter/Profile.h"
#include "ofx/Twitter/Entities.h"
#include "ofx/Twitter/BaseUser.h"


// Undefine Status from Xlib.h.
#undef Status


namespace ofx {
namespace Twitter {


class Status;


/// \sa https://dev.twitter.com/overview/api/users
class User: public BaseNamedUser
{
public:
    enum class WithheldScope
    {
        USER,
        STATUS
    };

    User();

    User(int64_t id,
         const std::string& screenName,
         const std::string& name);

    virtual ~User();

    bool contributorsEnabled() const;
    Poco::DateTime createdAt() const;
    bool defaultProfile() const;
    bool defaultProfileImage() const;
    std::string description() const;
    Entities entities() const;
    int64_t favouritesCount() const;
    bool wasFollowRequestSent() const;
    int64_t followersCount() const;
    int64_t friendsCount() const;
    bool isGeoEnabled() const;
    bool isTranslator() const;
    std::string language() const;
    int64_t listedCount() const;
    std::string location() const;
    Profile profile() const;
    bool isProtected() const;
    bool showsAllInlineMedia();

    /// \returns status or nullptr if not available.
    const Status* status() const;
    int64_t statusesCount() const;
    const std::string* timeZone() const;
    const std::string* url() const;
    const int64_t* utcOffset() const;
    bool verified() const;
    std::vector<std::string> withheldInCountries() const;
    WithheldScope withheldScope() const;

    std::string translatorType() const;

    static User fromJSON(const ofJson& json);

private:
    bool _contributorsEnabled = false;

    Poco::DateTime _createdAt;

    bool _defaultProfile = false;;

    bool _defaultProfileImage = false;

    bool _hasExtendedProfile = false;

    std::string _description;

    Entities _entities;

    bool _geoEnabled = false;

    int64_t _favouritesCount = -1;

    bool _followRequestSent = false;

    int64_t _followersCount = -1;

    int64_t _friendsCount = -1;

    bool _following = false;

    bool _isGeoEnabled = false;

    bool _isTranslator = false;

    bool _isTranslationEnabled = false;

    bool _protected = false;

    bool _verified = false;

    bool _notifications = false;

    std::string _language;

    int64_t _listedCount = -1;

    std::string _location;

    Profile _profile;

    bool _isProtected = false;

    bool _showsAllInlineMedia = false;

    /// \brief Optional Twitter status.
    ///
    /// We use a std::shared_ptr to keep track to make it nullable and avoid
    /// the hassle of std::unique_ptr and copies.
    std::shared_ptr<Status> _status;

    int64_t _statusesCount;

    std::shared_ptr<std::string> _timeZone;

    std::shared_ptr<std::string> _url;

    std::shared_ptr<int64_t> _UTCOffset;

    std::vector<std::string> _withheldInCountries;

    WithheldScope _withheldScope;

    std::string _translatorType;
};


} } // namespace ofx::Twitter
