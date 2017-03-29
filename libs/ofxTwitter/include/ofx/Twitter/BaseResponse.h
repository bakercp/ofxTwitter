//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include <vector>
#include "Poco/Net/NameValueCollection.h"
#include "ofx/HTTP/Response.h"
#include "ofx/Twitter/Error.h"


namespace ofx {
namespace Twitter {


class RateLimit
{
public:
    uint64_t limit() const
    {
        return _limit;
    }


    uint64_t remaining() const
    {
        return _remaining;
    }

    uint64_t reset() const
    {
        return _reset;
    }

    static RateLimit fromHeaders(const Poco::Net::NameValueCollection& headers)
    {
        RateLimit limit;
        limit._limit = std::stoull(headers.get("x-rate-limit-limit", "0"));
        limit._remaining = std::stoull(headers.get("x-rate-limit-remaining", "0"));
        limit._reset = std::stoull(headers.get("x-rate-limit-reset", "0"));
        return limit;
    }

private:
    uint64_t _limit = 0;
    uint64_t _remaining = 0;
    uint64_t _reset = 0;

};


class BaseResponse
{
public:
    virtual ~BaseResponse()
    {
    }

    std::vector<Error> errors() const
    {
        return _errors;
    }

    RateLimit rateLimit() const
    {
        return _limit;
    }

protected:
    RateLimit _limit;

    std::vector<Error> _errors;

};


} } // namespace ofx::Twitter
