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


std::string Credentials::consumerKey() const
{
    return _consumerKey;
}


std::string Credentials::consumerSecret() const
{
    return _consumerSecret;
}


std::string Credentials::accessToken() const
{
    return _accessToken;
}


std::string Credentials::accessTokenSecret() const
{
    return _accessTokenSecret;
}


Credentials Credentials::fromJSON(const ofJson& json)
{
    Credentials credentials;

    auto iter = json.cbegin();
    while (iter != json.cend())
    {
        const auto& key = iter.key();
        const auto& value = iter.value();

        if (key == "consumerKey") credentials._consumerKey = value;
        else if (key == "consumerSecret") credentials._consumerSecret = value;
        else if (key == "accessToken") credentials._accessToken = value;
        else if (key == "accessTokenSecret") credentials._accessTokenSecret = value;
        else ofLogWarning("Credentials::fromJSON") << "Unknown key: " << key << std::endl << value.dump(4);
        ++iter;
    }

    return credentials;
}


ofJson Credentials::toJSON(const Credentials& credentials)
{
    ofJson json;

    json["consumerKey"] = credentials._consumerKey;
    json["consumerSecret"] = credentials._consumerSecret;
    json["accessToken"] = credentials._accessToken;
    json["accessTokenSecret"] = credentials._accessTokenSecret;

    return json;
}


Credentials Credentials::fromFile(const std::string& credentialsFile)
{
    Credentials credentials;

    try
    {
        credentials = fromJSON(ofJson::parse(ofBufferFromFile(credentialsFile)));
    }
    catch (const std::exception& exception)
    {
        ofLogError("Credentials::fromFile") << exception.what();
    }

    return credentials;
}


bool Credentials::toFile(const Credentials& credentials,
                         const std::string& credentialsFile)
{
    ofJson json = toJSON(credentials);

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
