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
#include "ofx/Twitter/Entities.h"
#include "ofx/Twitter/BaseUser.h"


// Undefine Status from Xlib.h.
#undef Status


namespace ofx {
namespace Twitter {


class Status;


/// \brief A Twitter User.
/// \sa https://developer.twitter.com/en/docs/tweets/data-dictionary/overview/user-object
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

    /// \brief Get the user-defined location for this user.
    /// Not necessarily a location, nor machine-parseable. This field will
    /// occasionally be fuzzily interpreted by the Search service
    /// \returns The user-defined location for this account’s profile.
    std::string location() const;

    /// \returns A URL provided by the user in association with their profile.
    std::string url() const;

    /// \returns The user-defined UTF-8 string describing their account.
    std::string description() const;

    /// \brief Determine if the user's account is protected.
    /// When true, indicates that this user has chosen to protect their Tweets.
    /// \returns the protected status of a user's account.
    bool isProtected() const;

    /// \brief Determine if the user's account is verified.
    /// When true, indicates that the user has a verified account
    /// \returns the verified status of a user's account.
    /// \sa https://help.twitter.com/en/managing-your-account/about-twitter-verified-accounts
    bool isVerified() const;

    /// \brief Get the number of followers a user has.
    /// Under certain conditions of duress, this field will temporarily
    /// indicate "0".
    /// \returns The number of followers this account currently has.
    int64_t followersCount() const;

    /// \brief Get the number of friends a user has.
    /// The number of users this account is following (AKA their “followings”).
    /// Under certain conditions of duress, this field will temporarily
    /// indicate "0"
    int64_t friendsCount() const;

    /// \brief The number of public lists that this user is a member of.
    /// \returns The number of public lists that this user is a member of.
    int64_t listedCount() const;

    /// \brief Get number of Tweets this user has liked in the account’s lifetime.
    /// \returns The number of Tweets this user has liked in the account’s lifetime.
    int64_t favouritesCount() const;

    /// \returns the number of Tweets (including retweets) issued by the user.
    int64_t statusesCount() const;

    /// \returns The UTC datetime that the user account was created on Twitter
    Poco::DateTime createdAt() const;

    /// \brief Get the user's profile banner URL.
    /// The HTTPS-based URL pointing to the standard web representation of the
    /// user’s uploaded profile banner. By adding a final path element of the
    /// URL, it is possible to obtain different image sizes optimized for
    /// specific displays.
    /// \sa https://developer.twitter.com/en/docs/accounts-and-users/user-profile-images-and-banners
    /// \returns the profile babber url.
    std::string profileBannerUrl() const;

    /// \returns A HTTPS-based URL pointing to the user’s profile image.
    std::string profileImageUrlHttps() const;

    /// \returns true if the user has not altered the theme or background of their user profile.
    bool defaultProfile() const;

    /// \returns true if the user has not altered the profile image of their user profile.
    bool defaultProfileImage() const;

    /// \brief Get a list of countries this user has been witheld from.
    ///
    /// e.g.
    /// “XX” - Content is withheld in all countries “XY” - Content is withheld
    /// due to a DMCA request.
    ///
    /// \returns a list of countries.
    std::vector<std::string> withheldInCountries() const;

    /// \returns the the scope of the content being witheld.
    WithheldScope withheldScope() const;

    Entities entities() const;

    bool showsAllInlineMedia();

    /// \returns status or nullptr if not available.
    const Status* status() const;

    static User fromJSON(const ofJson& json);

private:
    Poco::DateTime _createdAt;
    std::string _profileBannerUrl;
    bool _defaultProfile = false;;
    bool _defaultProfileImage = false;
    std::string _description;
    Entities _entities;
    int64_t _favouritesCount = -1;
    int64_t _followersCount = -1;
    int64_t _friendsCount = -1;
    bool _protected = false;
    bool _isVerified = false;
    int64_t _listedCount = -1;
    std::string _location;
    bool _isProtected = false;
    bool _showsAllInlineMedia = false;

    /// \brief Optional Twitter status.
    ///
    /// We use a std::shared_ptr to keep track to make it nullable and avoid
    /// the hassle of std::unique_ptr and copies.
    std::shared_ptr<Status> _status;

    int64_t _statusesCount;
    std::string _url;
    std::string _profileImageUrlHttps;

    std::vector<std::string> _withheldInCountries;
    WithheldScope _withheldScope;

};


} } // namespace ofx::Twitter
