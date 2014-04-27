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


#include "ofx/Twitter/Deserializer.h"


namespace ofx {
namespace Twitter {


const std::string Deserializer::TWITTER_DATE_FORMAT = "%w %b %f %H:%M:%S %Z %Y";


bool Deserializer::deserialize(const Json::Value& json, User& user)
{
    if(json.isMember("id"))
    {
        user._ID = json["id"].asInt64();
    }

    if(json.isMember("screen_name"))
    {
        user._screenName = json["screen_name"].asString();
    }

    if(json.isMember("name"))
    {
        user._name = json["name"].asString();
    }

    // etc

    return true;
}

bool Deserializer::deserialize(const Json::Value& json, BaseNamedUser& user)
{
    if(json.isMember("id"))
    {
        user._ID = json["id"].asInt64();
    }

    if(json.isMember("screen_name"))
    {
        user._screenName = json["screen_name"].asString();
    }
    if(json.isMember("name"))
    {
        user._name = json["name"].asString();
    }

    return true;
}

bool Deserializer::deserialize(const Json::Value& json, BaseUser& user)
{
    if(json.isMember("id"))
    {
        user._ID = json["id"].asInt64();
    }

    if(json.isMember("screen_name"))
    {
        user._screenName = json["screen_name"].asString();
    }

    return true;
}


bool Deserializer::deserialize(const std::string& jsonString, std::vector<Tweet>& tweets)
{
    Json::Value json;

    if (Deserializer::parse(jsonString, json))
    {
        if (json.isMember("statuses"))
        {
            Json::Value statuses = json["statuses"];

            Tweet tweet;

            for (Json::ArrayIndex i = 0; i < statuses.size(); ++i)
            {
                Json::Value status = statuses[i];

                if (status.isMember("id"))
                    tweet._ID = status["id"].asInt64();
                if (status.isMember("text"))
                    tweet._text = status["text"].asString();
                if (status.isMember("utc_offset"))
                    tweet._utcOffset = status["utc_offset"].asInt64();

                if (status.isMember("created_at"))
                {
                    Poco::DateTime date;

                    if (parse(statuses[i]["created_at"].asString(), date))
                    {
                        tweet._createdAt = date;

                        if (status.isMember("utc_offset"))
                        {
                            // date.makeUTC(status.isMember("utc_offset"))
                        }
                    }
                }

                if (status.isMember("user"))
                {
                    User user;
                    if(deserialize(status["user"], user))
                        tweet._user = user;
                }

                tweets.push_back(tweet);
            }
        }
        else
        {
            ofLogError("deserialize") << "Found no statuses.";
            return false;
        }
        
        return true;
    }
    else
    {
        return false;
    }
}


bool Deserializer::parse(const std::string& jsonString, Json::Value& json)
{
    Json::Reader reader;

    if(reader.parse(jsonString, json))
    {
		return true;
	}
    else
    {
		ofLogError("Deserializer::parse") << "Unable to parse string: " << reader.getFormattedErrorMessages();
        return false;
    }
}

bool Deserializer::parse(const std::string& dateString, Poco::DateTime& date)
{
    try
    {
        int tzd;
        Poco::DateTimeParser::parse(TWITTER_DATE_FORMAT, dateString, date, tzd);
    }
    catch (Poco::SyntaxException& exc)
    {
		ofLogError("Deserializer::parse") << "Unable to parse date time string: " << exc.displayText();
        return false;
    }
}


} } // namespace ofx::Twitter
