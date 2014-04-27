// =============================================================================
//
// Copyright (c) 2009-2013 Christopher Baker <http://christopherbaker.net>
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


#include <string>
#include <json/json.h>
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeParser.h"
#include "Poco/DateTime.h"
#include "ofLog.h"
#include "ofx/Twitter/Entities.h"
#include "ofx/Twitter/Places.h"
#include "ofx/Twitter/User.h"
#include "ofx/Twitter/Types.h"
#include "ofx/Twitter/Tweet.h"


namespace ofx {
namespace Twitter {


class Deserializer
{
public:
    static bool deserialize(const Json::Value& json, User& user);
    static bool deserialize(const Json::Value& json, BaseNamedUser& user);
    static bool deserialize(const Json::Value& json, BaseUser& user);

    static bool deserialize(const std::string& rawJson, std::vector<Tweet>& tweets);

    static bool parse(const std::string& jsonString, Json::Value& json);
    static bool parse(const std::string& dateString, Poco::DateTime& date);

    static const std::string TWITTER_DATE_FORMAT;

};


} } // namespace ofx::Twitter
