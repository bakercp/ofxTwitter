//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/Twitter/BaseUser.h"
#include "ofLog.h"


namespace ofx {
namespace Twitter {


BaseUser::BaseUser()
{
}


BaseUser::BaseUser(int64_t id, const std::string& screenName):
    _id(id),
    _screenName(screenName)
{
}


BaseUser::~BaseUser()
{
}


int64_t BaseUser::id() const
{
    return _id;
}


std::string BaseUser::screenName() const
{
    return _screenName;
}


BaseNamedUser::BaseNamedUser()
{
}


BaseNamedUser::BaseNamedUser(int64_t id,
                             const std::string& screenName,
                             const std::string& name):
    BaseUser(id, screenName),
    _name(name)
{
}


BaseNamedUser::~BaseNamedUser()
{
}


std::string BaseNamedUser::name() const
{
    return _name;
}


} } // namespace ofx::Twitter
