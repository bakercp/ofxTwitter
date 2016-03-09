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


#pragma once


#include <string>
#include <json/json.h>


namespace ofx {
namespace Twitter {


class Credentials
{
public:
    Credentials();

    Credentials(const std::string& consumerKey,
                const std::string& consumerSecret);

    Credentials(const std::string& consumerKey,
                const std::string& consumerSecret,
                const std::string& accessToken,
                const std::string& accessTokentSecret);

    /// \brief Destroy the Credentials.
    virtual ~Credentials();

    const std::string& getConsumerKey() const;

    const std::string& getConsumerSecret() const;

    const std::string& getAccessToken() const;

    const std::string& getAccessTokenSecret() const;

    static Credentials fromJSON(const Json::Value& value);

    static Json::Value toJSON(const Credentials& credentials);

    static Credentials fromFile(const std::string& credentialsFile);

    static bool toFile(const Credentials& credentials,
                       const std::string& credentialsFile);

private:
    /// \brief The consumer key.
    std::string _consumerKey;
    std::string _consumerSecret;
    std::string _accessToken;
    std::string _accessTokenSecret;

};


} } // namespace ofx::Twitter
