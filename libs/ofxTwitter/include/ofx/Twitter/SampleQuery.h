//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include "ofx/Twitter/StreamingQuery.h"


namespace ofx {
namespace Twitter {


/// \brief Parameters needed to request Twitter Streams.
/// \sa https://dev.twitter.com/streaming/overview/request-parameters
class SampleQuery: public StreamingQuery
{
public:
    virtual ~SampleQuery();

    static const std::string RESOURCE_URL;

};


} } // namespace ofx::Twitter
