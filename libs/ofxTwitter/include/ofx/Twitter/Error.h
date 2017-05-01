//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include <string>
#include "ofJson.h"


namespace ofx {
namespace Twitter {


/// \brief Twitter Response/Error codes.
/// \sa https://dev.twitter.com/overview/api/response-codes
class Error
{
public:
    /// \brief Construct a default Error.
    Error();

    /// \brief Construct an Error with a 64-bit code and message string.
    /// \param code The 64-bit error code.
    /// \param message The error message.
    Error(int64_t code, const std::string& message);

    /// \brief Destroy the Error.
    virtual ~Error();

    /// \returns the error code.
    int64_t code() const;

    /// \returns the error message.
    std::string message() const;

    /// \returns the Error as JSON.
    ofJson toJSON() const;

    /// \brief Deserialize an Error from JSON.
    /// \param json The JSON representing the Error.
    /// \returns the Error.
    static Error fromJSON(const ofJson& json);

private:
    /// \brief The 64-bit Error code.
    int64_t _code = -1;

    /// \brief The Error message.
    std::string _message;

};


} } // namespace ofx::Twitter
