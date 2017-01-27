//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include "json.hpp"
#include <string>


namespace ofx {
namespace Twitter {


/// \brief Twitter Response/Error codes.
/// \sa https://dev.twitter.com/overview/api/response-codes
class Error
{
public:
    Error();

    Error(int64_t code, const std::string& message);

    virtual ~Error();

    int64_t code() const;

    std::string message() const;

    static Error fromJSON(const ofJson& json);

private:
    int64_t _code = -1;
    std::string _message;

};


} } // namespace ofx::Twitter
