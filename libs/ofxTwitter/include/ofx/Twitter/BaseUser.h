//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include <string>
#include <set>
#include "ofJson.h"


namespace ofx {
namespace Twitter {


/// \brief A base class for a Twitter user.
class BaseUser
{
public:
    /// \brief Construt an unintialized user.
    BaseUser();

    /// \brief Construct a user with an 64-bit id.
    /// \param id The 64-bit user id.
    BaseUser(int64_t id);

    /// \brief Construct a user with an 64-bit id and screen name.
    /// \param id The 64-bit user id.
    /// \param screenName The user's screen name.
    BaseUser(int64_t id, const std::string& screenName);

    /// \brief Destroy the BaseUser.
    virtual ~BaseUser();

    /// \returns the user id.
    int64_t id() const;

    /// \returns the user's screen name or empty if unavailable.
    std::string screenName() const;

protected:
    /// \brief The user id.
    int64_t _id = -1;

    /// \brief The user screen name.
    std::string _screenName;

};


/// \brief A base class for a named Twitter user.
class BaseNamedUser: public BaseUser
{
public:
    /// \brief Create a default BaseNamedUser.
    BaseNamedUser();

    /// \brief Construct a user with an 64-bit id.
    /// \param id The 64-bit user id.
    BaseNamedUser(int64_t id);

    /// \brief Construct a user with an 64-bit id and screen name.
    /// \param id The 64-bit user id.
    /// \param screenName The user's screen name.
    BaseNamedUser(int64_t id,
                  const std::string& screenName);

    /// \brief Construct a user with an 64-bit id and screen name.
    /// \param id The 64-bit user id.
    /// \param screenName The user's screen name.
    /// \param name The user's real name.
    BaseNamedUser(int64_t id,
                  const std::string& screenName,
                  const std::string& name);

    /// \brief Destroy
    virtual ~BaseNamedUser();

    /// \returns the user's name if available.
    std::string name() const;

protected:
    /// \brief The user's name.
    std::string _name;

};


} } // namespace ofx::Twitter
