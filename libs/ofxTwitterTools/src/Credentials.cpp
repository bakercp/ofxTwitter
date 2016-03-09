// =============================================================================
//
// Copyright (c) 2009-2016 Christopher Baker <http://christopherbaker.net>
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


#include "ofx/Twitter/Credentials.h"
#include "ofx/IO/ByteBuffer.h"
#include "ofx/IO/ByteBufferUtils.h"
#include "Poco/Exception.h"
#include "Poco/FileStream.h"
#include "ofLog.h"
#include "ofUtils.h"


namespace ofx {
namespace Twitter {


Credentials::Credentials()
{
}


Credentials::Credentials(const std::string& consumerKey,
                         const std::string& consumerSecret):
    _consumerKey(consumerKey),
    _consumerSecret(consumerSecret)
{
}


Credentials::Credentials(const std::string& consumerKey,
                         const std::string& consumerSecret,
                         const std::string& accessToken,
                         const std::string& accessTokenSecret):
    _consumerKey(consumerKey),
    _consumerSecret(consumerSecret),
    _accessToken(accessToken),
    _accessTokenSecret(accessTokenSecret)
{
}


Credentials::~Credentials()
{
}


const std::string& Credentials::getConsumerKey() const
{
    return _consumerKey;
}


const std::string& Credentials::getConsumerSecret() const
{
    return _consumerSecret;
}


const std::string& Credentials::getAccessToken() const
{
    return _accessToken;
}


const std::string& Credentials::getAccessTokenSecret() const
{
    return _accessTokenSecret;
}


Credentials Credentials::fromJSON(const Json::Value& value)
{
    Credentials credentials;

    if (value.isMember("consumerKey") && value["consumerKey"].isString())
    {
        credentials._consumerKey = value["consumerKey"].asString();
    }

    if (value.isMember("consumerSecret") && value["consumerSecret"].isString())
    {
        credentials._consumerSecret = value["consumerSecret"].asString();
    }

    if (value.isMember("accessToken") && value["accessToken"].isString())
    {
        credentials._accessToken = value["accessToken"].asString();
    }

    if (value.isMember("accessTokenSecret") && value["accessTokenSecret"].isString())
    {
        credentials._accessTokenSecret = value["accessTokenSecret"].asString();
    }

    return credentials;
}


Json::Value Credentials::toJSON(const Credentials& credentials)
{
    Json::Value value;

    value["consumerKey"] = credentials._consumerKey;
    value["consumerSecret"] = credentials._consumerSecret;
    value["accessToken"] = credentials._accessToken;
    value["accessTokenSecret"] = credentials._accessTokenSecret;

    return value;
}


Credentials Credentials::fromFile(const std::string& credentialsFile)
{
    Credentials credentials;

    try
    {
        IO::ByteBuffer buffer;
        IO::ByteBufferUtils::loadFromFile(ofToDataPath(credentialsFile, true), buffer);

        Json::Reader reader;
        Json::Value json;

        if (!reader.parse(buffer.toString(), json))
        {
            throw Poco::IOException("Unable to parse " + credentialsFile + ": " + reader.getFormattedErrorMessages());
        }
        else
        {
            credentials = fromJSON(json);
        }
    }
    catch (const Poco::Exception& exception)
    {
        ofLogError("Credentials::fromFile") << exception.displayText();
    }

    return credentials;

}


bool Credentials::toFile(const Credentials& credentials,
                         const std::string& credentialsFile)
{
    Json::Value json = toJSON(credentials);

    try
    {
        Poco::FileOutputStream fos(ofToDataPath(credentialsFile, true));

        if (fos.good())
        {
            fos << json;
            fos.close();
            return true;
        }
        else
        {
            throw Poco::IOException("Bad file output stream.");
        }
    }
    catch (const Poco::Exception& exception)
    {
        ofLogError("Credentials::toFile") << exception.displayText();
        return false;
    }

    return true;
}


} } // namespace ofx::Twitter
