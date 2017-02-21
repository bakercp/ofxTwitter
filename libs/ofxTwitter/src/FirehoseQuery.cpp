//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/Twitter/FirehoseQuery.h"


namespace ofx {
namespace Twitter {


const std::string FirehoseQuery::RESOURCE_URL = "https://stream.twitter.com/1.1/statuses/firehose.json";


FirehoseQuery::~FirehoseQuery()
{
}


} } // namespace ofx::Twitter
