//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//



#pragma once


#include "Poco/Net/NameValueCollection.h"
#include "ofThreadChannel.h"
#include "ofx/HTTP/OAuth10HTTPClient.h"
#include "ofx/IO/Thread.h"
#include "ofx/IO/ThreadChannel.h"
#include "ofx/Twitter/Notices.h"
#include "ofx/Twitter/Status.h"
#include "ofx/Twitter/SampleQuery.h"
#include "ofx/Twitter/FilterQuery.h"


namespace ofx {
namespace Twitter {


/// \brief Base Twitter API client.
class BaseClient
{
public:
    /// \brief Create a BaseClient.
    BaseClient();

    BaseClient(const HTTP::OAuth10Credentials& credentials);

    /// \brief Destroy the BaseClient.
    virtual ~BaseClient();

    /// \brief Create an unconnected BaseClient with given parameters.
    /// \param credentials The OAuth 1.0 credentials to use.
    /// \brief Set the credentials from a JSON configuration file.
    /// \param credentialsPath A path to the credentials JSON file.
    void setCredentialsFromFile(const std::filesystem::path& credentialsPath);

    /// \brief Set the credentials from a JSON object.
    /// \param credentials The JSON object representing the credentials.
    void setCredentialsFromJson(const ofJson& credentials);

    /// \brief Set the credentials from a HTTP::OAuth10Credentials object.
    /// \param credentials The HTTP::OAuth10Credentials object.
    void setCredentials(const HTTP::OAuth10Credentials& credentials);

    /// \returns the current credentials.
    HTTP::OAuth10Credentials getCredentials() const;

    /// \brief The BaseClient user agent.
    ///
    /// Both the `User-Agent` and `X-User-Agent` are set to this value.
    static const std::string USER_AGENT;

protected:
//    virtual void _onStatus(const Status& status) = 0;
//    virtual void _onException(const std::exception& exc) = 0;
//    virtual void _onMessage(const ofJson& message) = 0;

    HTTP::OAuth10Credentials _credentials;
    HTTP::OAuth10HTTPClient _client;
//private:
//    HTTP::OAuth10Credentials _credentials;
//    HTTP::OAuth10HTTPClient _client;
};


} } // namespace ofx::Twitter
