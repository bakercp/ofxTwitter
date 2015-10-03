// =============================================================================
//
// Copyright (c) 2009-2015 Christopher Baker <http://christopherbaker.net>
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


#include <vector>
#include <json/json.h>
#include "ofx/Twitter/Error.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Exception.h"


namespace ofx {
namespace Twitter {


class BaseTwitterResponse
{
public:
    BaseTwitterResponse(Poco::Net::HTTPResponse::HTTPStatus status);

    virtual ~BaseTwitterResponse();

    const std::vector<Error>& errors() const;

    Poco::Net::HTTPResponse::HTTPStatus status() const;

    /// \brief Get the reason for the HTTP Response.
    ///
    /// Sub-classes can override this method to provide Twitter-specific
    /// reasons.
    ///
    /// \returns A string describing the reasons for the HTTP status.
    virtual std::string reasonForStatus() const;

    const Json::Value& json() const;

protected:
    Json::Value _json;

    Poco::Net::HTTPResponse::HTTPStatus _status;

    std::vector<Error> _errors;

    friend class Deserilizer;
    
};


} } // namespace ofx::Twitter
