//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/Twitter/Error.h"
#include "ofLog.h"


namespace ofx {
namespace Twitter {


Error::Error()
{
}


Error::Error(int64_t code, const std::string& message):
    _code(code),
    _message(message)
{
}


Error::~Error()
{
}


int64_t Error::code() const
{
    return _code;
}


std::string Error::message() const
{
    return _message;
}


ofJson Error::toJSON() const
{
    ofJson json;
    json["code"] = _code;
    json["message"] = _message;
    return json;
}


Error Error::fromJSON(const ofJson& json)
{
    Error error;

    auto iter = json.cbegin();
    while (iter != json.cend())
    {
        const auto& key = iter.key();
        const auto& value = iter.value();

        if (key == "code") error._code = value;
        else if (key == "message") error._message = value;
        else ofLogWarning("Error::fromJSON") << "Unknown key: " << key;

        ++iter;
    }

    return error;
}


} } // namespace ofx::Twitter
