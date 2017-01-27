//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include <string>
#include <set>
#include "json.hpp"


namespace ofx {
namespace Twitter {


class BaseUser
{
public:
    BaseUser();
    BaseUser(int64_t id, const std::string& screenName);

    virtual ~BaseUser();

    /// \returns the user id.
    int64_t id() const;

    /// \returns the user's screen name.
    std::string screenName() const;

protected:
    /// \brief The user id.
    int64_t _id = -1;

    /// \brief The user screen name.
    std::string _screenName;

};


class BaseNamedUser: public BaseUser
{
public:
    BaseNamedUser();

    BaseNamedUser(int64_t id,
                  const std::string& screenName,
                  const std::string& name);

    virtual ~BaseNamedUser();

    /// \returns the User's name.
    std::string name() const;

    static BaseNamedUser fromJSON(const ofJson& json);

protected:
    /// \brief The User's name.
    std::string _name;

};


} } // namespace ofx::Twitter
