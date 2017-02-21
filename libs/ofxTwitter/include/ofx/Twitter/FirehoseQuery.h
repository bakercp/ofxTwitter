//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include "ofx/Twitter/StreamingQuery.h"


namespace ofx {
namespace Twitter {


/// \brief Parameters needed to request firehose Twitter Streams.
/// \sa https://dev.twitter.com/streaming/reference/get/statuses/firehose
class FirehoseQuery: public StreamingQuery
{
public:
    virtual ~FirehoseQuery();

    static const std::string RESOURCE_URL;
    
};


} } // namespace ofx::Twitter
