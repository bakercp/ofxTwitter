//
// Copyright (c) 2019 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/Twitter/BaseClient.h"


namespace ofx {
namespace Twitter {


const std::string BaseClient::USER_AGENT = "ofxTwitter (compatible; Client/1.0 +https://github.com/bakercp/ofxTwitter)";


BaseClient::BaseClient()
{
}


BaseClient::BaseClient(const HTTP::OAuth10Credentials& credentials):
    _credentials(credentials)
{
}


BaseClient::~BaseClient()
{
}


void BaseClient::setCredentialsFromFile(const std::filesystem::path& credentialsPath)
{
    setCredentials(HTTP::OAuth10Credentials::fromFile(credentialsPath));
}


void BaseClient::setCredentialsFromJson(const ofJson& credentials)
{
    setCredentials(HTTP::OAuth10Credentials::fromJSON(credentials));
}


void BaseClient::setCredentials(const HTTP::OAuth10Credentials& credentials)
{
    _credentials = credentials;
}


HTTP::OAuth10Credentials BaseClient::getCredentials() const
{
    return _credentials;
}


//void BaseClient::_run()
//{
//    HTTP::ClientSessionSettings sessionSettings;
//    sessionSettings.addDefaultHeader("X-User-Agent", USER_AGENT);
//    sessionSettings.setUserAgent(USER_AGENT);
//    sessionSettings.setTimeout(TIMEOUT * Poco::Timespan::MILLISECONDS);
//    _client.context().setClientSessionSettings(sessionSettings);
//    _client.setCredentials(_credentials);
//
//    try
//    {
//        _lastMessageTime = ofGetElapsedTimeMillis();
//
//        _onConnect();
//
//        HTTP::FormRequest request(_httpMethod,
//                                  _url,
//                                  Poco::Net::HTTPMessage::HTTP_1_1);
//
//        request.addFormFields(_parameters);
//
//        auto response = _client.execute(request);
//
//        if (!response->isSuccess())
//        {
//            ofBuffer result = response->buffer();
//
//            ofLogError("BaseStreamingClient::_run") << result;
//        }
//        else
//        {
//            std::istream& istr = response->stream();
//            std::string line;
//
//            while (isRunning() && std::getline(istr, line))
//            {
//                _lastMessageTime = ofGetElapsedTimeMillis();
//
//                if (!istr.fail())
//                {
//                    try
//                    {
//                        // Parsing should take care of any leading / trailing
//                        // whitespace or new line characters that weren't
//                        // consumed by std::getline.
//                        ofJson json = ofJson::parse(line);
//
//                        if (json.is_null() || json.empty())
//                        {
//                            continue;
//                        }
//                        else
//                        {
//                            _onMessage(json);
//                        }
//
//
//                        if (json.find(StatusDeletedNotice::JSON_KEY) != json.end())
//                        {
//                            _onStatusDeletedNotice(StatusDeletedNotice::fromJSON(json[StatusDeletedNotice::JSON_KEY]));
//                        }
//                        else if (json.find(LocationDeletedNotice::JSON_KEY) != json.end())
//                        {
//                            _onLocationDeletedNotice(LocationDeletedNotice::fromJSON(json[LocationDeletedNotice::JSON_KEY]));
//                        }
//                        else if (json.find(LimitNotice::JSON_KEY) != json.end())
//                        {
//                            _onLimitNotice(LimitNotice::fromJSON(json[LimitNotice::JSON_KEY]));
//                        }
//                        else if (json.find(StatusWithheldNotice::JSON_KEY) != json.end())
//                        {
//                            _onStatusWithheldNotice(StatusWithheldNotice::fromJSON(json[StatusWithheldNotice::JSON_KEY]));
//                        }
//                        else if (json.find(UserWithheldNotice::JSON_KEY) != json.end())
//                        {
//                            _onUserWitheldNotice(UserWithheldNotice::fromJSON(json[UserWithheldNotice::JSON_KEY]));
//                        }
//                        else if (json.find(DisconnectNotice::JSON_KEY) != json.end())
//                        {
//                            _onDisconnectNotice(DisconnectNotice::fromJSON(json[DisconnectNotice::JSON_KEY]));
//                        }
//                        else if (json.find(StallWarning::JSON_KEY) != json.end())
//                        {
//                            _onStallWarning(StallWarning::fromJSON(json[StallWarning::JSON_KEY]));
//                        }
//                        else if (json.find("text") != json.end())
//                        {
//                            _onStatus(Status::fromJSON(json));
//                        }
//                    }
//                    catch (const std::exception& exc)
//                    {
//                        // Only pass exception if still running.
//                        if (isRunning())
//                        {
//                            ofLogError("BaseStreamingClient::_run") << exc.what();
//                            _onException(std::exception(exc));
//                        }
//                    }
//                }
//            }
//        }
//    }
//    catch (const Poco::Exception& exc)
//    {
//        ofLogError("BaseStreamingClient::_run") << exc.displayText();
//        _onException(std::exception(exc));
//    }
//    catch (const std::exception& exc)
//    {
//        ofLogError("BaseStreamingClient::_run") << exc.what();
//        _onException(std::exception(exc));
//    }
//    catch (...)
//    {
//        Poco::Exception exc("Unknown exception.");
//        ofLogError("BaseStreamingClient::_run") << exc.displayText();
//        _onException(std::exception(exc));
//    }

//    _onDisconnect();

//}

    
} } // namespace ofx::Twitter
