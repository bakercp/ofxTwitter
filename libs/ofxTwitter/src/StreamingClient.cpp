//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/Twitter/StreamingClient.h"
#include "ofx/HTTP/HTTPUtils.h"
#include "ofx/HTTP/GetRequest.h"
#include "ofx/HTTP/PostRequest.h"
#include "ofx/IO/ByteBufferUtils.h"
#include "ofx/Twitter/User.h"


namespace ofx {
namespace Twitter {


const uint64_t BaseStreamingClient::TIMEOUT = 90000;
const std::string BaseStreamingClient::USER_AGENT = "ofxTwitter (compatible; Client/1.0 +https://github.com/bakercp/ofxTwitter)";


BaseStreamingClient::BaseStreamingClient():
    BaseStreamingClient(HTTP::OAuth10Credentials())
{
}


BaseStreamingClient::BaseStreamingClient(const HTTP::OAuth10Credentials& credentials):
    IO::Thread(std::bind(&BaseStreamingClient::_run, this)),
    _credentials(credentials)
{
}


BaseStreamingClient::~BaseStreamingClient()
{
}


void BaseStreamingClient::setCredentialsFromFile(const std::filesystem::path& credentialsPath)
{
    setCredentials(HTTP::OAuth10Credentials::fromFile(credentialsPath));
}


void BaseStreamingClient::setCredentialsFromJson(const ofJson& credentials)
{
    setCredentials(HTTP::OAuth10Credentials::fromJSON(credentials));
}


void BaseStreamingClient::setCredentials(const HTTP::OAuth10Credentials& credentials)
{
    std::unique_lock<std::mutex> lock(mutex);
    _credentials = credentials;
}


void BaseStreamingClient::onStopRequested()
{
    if (_client.context().clientSession())
    {
        try
        {
            _client.context().clientSession()->abort();
        }
        catch (const Poco::Exception& exc)
        {
            ofLogWarning("BaseStreamingClient::disconnect")  << exc.displayText();
        }
    }
}


HTTP::OAuth10Credentials BaseStreamingClient::getCredentials() const
{
    std::unique_lock<std::mutex> lock(mutex);
    return _credentials;
}


BaseStreamingClient::StreamType BaseStreamingClient::streamType() const
{
    std::unique_lock<std::mutex> lock(mutex);
    return _streamType;
}


void BaseStreamingClient::sample()
{
    sample(SampleQuery());
}


void BaseStreamingClient::sample(const SampleQuery& query)
{
    stopAndJoin();
    _streamType = StreamType::SAMPLE;
    _parameters = query;
    _httpMethod = Poco::Net::HTTPRequest::HTTP_GET;
    _url = SampleQuery::RESOURCE_URL;
    start();
}


void BaseStreamingClient::filter(std::vector<std::string> track,
                                 std::vector<std::string> follow,
                                 std::vector<Geo::CoordinateBounds> locations)
{
    FilterQuery query;
    query.setTracks(track);
    query.setFollows(follow);
    query.setLocations(locations);
    filter(query);
}


void BaseStreamingClient::filter(const FilterQuery& query)
{
    stopAndJoin();
    _streamType = StreamType::FILTER;
    _parameters = query;
    _httpMethod = Poco::Net::HTTPRequest::HTTP_POST;
    _url = FilterQuery::RESOURCE_URL;
    start();
}


void BaseStreamingClient::user(const UserFilterQuery& query)
{
    stopAndJoin();
    _streamType = StreamType::USER;
    _parameters = query;
    _httpMethod = Poco::Net::HTTPRequest::HTTP_GET;
    _url = UserFilterQuery::RESOURCE_URL;
    start();
}


void BaseStreamingClient::_run()
{
    HTTP::ClientSessionSettings sessionSettings;
    sessionSettings.addDefaultHeader("X-User-Agent", USER_AGENT);
    sessionSettings.setUserAgent(USER_AGENT);
    sessionSettings.setTimeout(TIMEOUT * Poco::Timespan::MILLISECONDS);
    _client.context().setClientSessionSettings(sessionSettings);
    _client.setCredentials(_credentials);

    try
    {
        _lastMessageTime = ofGetElapsedTimeMillis();

        _onConnect();

        HTTP::FormRequest request(_httpMethod,
                                  _url,
                                  Poco::Net::HTTPMessage::HTTP_1_1);

        request.addFormFields(_parameters);

        auto response = _client.execute(request);

        if (!response->isSuccess())
        {
            ofBuffer result = response->buffer();

            ofLogError("BaseStreamingClient::_run") << result;
        }
        else
        {
            std::istream& istr = response->stream();
            std::string line;

            while (isRunning() && std::getline(istr, line))
            {
                _lastMessageTime = ofGetElapsedTimeMillis();

                if (!istr.fail())
                {
                    try
                    {
                        // Parsing should take care of any leading / trailing
                        // whitespace or new line characters that weren't
                        // consumed by std::getline.
                        ofJson json = ofJson::parse(line);

                        if (json.is_null() || json.empty())
                        {
                            continue;
                        }
                        else
                        {
                            _onMessage(json);
                        }


                        if (json.find(StatusDeletedNotice::JSON_KEY) != json.end())
                        {
                            _onStatusDeletedNotice(StatusDeletedNotice::fromJSON(json[StatusDeletedNotice::JSON_KEY]));
                        }
                        else if (json.find(LocationDeletedNotice::JSON_KEY) != json.end())
                        {
                            _onLocationDeletedNotice(LocationDeletedNotice::fromJSON(json[LocationDeletedNotice::JSON_KEY]));
                        }
                        else if (json.find(LimitNotice::JSON_KEY) != json.end())
                        {
                            _onLimitNotice(LimitNotice::fromJSON(json[LimitNotice::JSON_KEY]));
                        }
                        else if (json.find(StatusWithheldNotice::JSON_KEY) != json.end())
                        {
                            _onStatusWithheldNotice(StatusWithheldNotice::fromJSON(json[StatusWithheldNotice::JSON_KEY]));
                        }
                        else if (json.find(UserWithheldNotice::JSON_KEY) != json.end())
                        {
                            _onUserWitheldNotice(UserWithheldNotice::fromJSON(json[UserWithheldNotice::JSON_KEY]));
                        }
                        else if (json.find(DisconnectNotice::JSON_KEY) != json.end())
                        {
                            _onDisconnectNotice(DisconnectNotice::fromJSON(json[DisconnectNotice::JSON_KEY]));
                        }
                        else if (json.find(StallWarning::JSON_KEY) != json.end())
                        {
                            _onStallWarning(StallWarning::fromJSON(json[StallWarning::JSON_KEY]));
                        }
                        else if (json.find("text") != json.end())
                        {
                            _onStatus(Status::fromJSON(json));
                        }
                    }
                    catch (const std::exception& exc)
                    {
                        // Only pass exception if still running.
                        if (isRunning())
                        {
                            ofLogError("BaseStreamingClient::_run") << exc.what();
                            _onException(std::exception(exc));
                        }
                    }
                }
            }
        }
    }
    catch (const Poco::Exception& exc)
    {
        ofLogError("BaseStreamingClient::_run") << exc.displayText();
        _onException(std::exception(exc));
    }
    catch (const std::exception& exc)
    {
        ofLogError("BaseStreamingClient::_run") << exc.what();
        _onException(std::exception(exc));
    }
    catch (...)
    {
        Poco::Exception exc("Unknown exception.");
        ofLogError("BaseStreamingClient::_run") << exc.displayText();
        _onException(std::exception(exc));
    }

    _onDisconnect();

}


StreamingClient::StreamingClient(bool autoEventSync):
    StreamingClient(HTTP::OAuth10Credentials())
{
}


StreamingClient::StreamingClient(const HTTP::OAuth10Credentials& credentials,
                                 bool autoEventSync):
    BaseStreamingClient(credentials)
{
    setAutoEventSync(autoEventSync);
}


StreamingClient::~StreamingClient()
{
}


void StreamingClient::setAutoEventSync(bool value)
{
    if (value)
    {
        _updateListener = ofEvents().update.newListener(this, &StreamingClient::_update);
        _exitListener = ofEvents().exit.newListener(this, &StreamingClient::_exit);
    }
    else
    {
        _updateListener.unsubscribe();
        _exitListener.unsubscribe();
    }

    _autoEventSync = value;
}


void StreamingClient::syncEvents()
{
    for (const auto& v: _connectChannel.tryReceiveAll()) onConnect.notify(this);
    for (const auto& v: _disconnectChannel.tryReceiveAll()) onDisconnect.notify(this);
    for (const auto& v: _statusChannel.tryReceiveAll()) onStatus.notify(this, v);
    for (const auto& v: _statusDeletedNoticeChannel.tryReceiveAll()) onStatusDeletedNotice.notify(this, v);
    for (const auto& v: _locationDeletedNoticeChannel.tryReceiveAll()) onLocationDeletedNotice.notify(this, v);
    for (const auto& v: _limitNoticeChannel.tryReceiveAll()) onLimitNotice.notify(this, v);
    for (const auto& v: _statusWithheldNoticeChannel.tryReceiveAll()) onStatusWithheldNotice.notify(this, v);
    for (const auto& v: _userWithheldNoticeChannel.tryReceiveAll()) onUserWitheldNotice.notify(this, v);
    for (const auto& v: _disconnectNoticeChannel.tryReceiveAll()) onDisconnectNotice.notify(this, v);
    for (const auto& v: _stallwarningChannel.tryReceiveAll()) onStallWarning.notify(this, v);
    for (const auto& v: _exceptionChannel.tryReceiveAll()) onException.notify(this, v);
    for (const auto& v: _messageChannel.tryReceiveAll()) onMessage.notify(this, v);

    uint64_t now = ofGetElapsedTimeMillis();

    // Disconnect if no new message has arrived and the socket hasn't timed out.
    if (isRunning() && now > (_lastMessageTime + TIMEOUT))
    {
        Poco::TimeoutException exc("No data received in " + std::to_string(TIMEOUT) + " ms. Disconnecting.");
        onException.notify(this, exc);
        stop();
    }
}


void StreamingClient::_update(ofEventArgs& args)
{
    syncEvents();
}


void StreamingClient::_exit(ofEventArgs& args)
{
    syncEvents();
}


void StreamingClient::_onConnect()
{
    _connectChannel.send(ofEventArgs());
}


void StreamingClient::_onDisconnect()
{
    _disconnectChannel.send(ofEventArgs());
}


void StreamingClient::_onStatus(const Status& status)
{
    _statusChannel.send(status);
}


void StreamingClient::_onStatusDeletedNotice(const StatusDeletedNotice& notice)
{
    _statusDeletedNoticeChannel.send(notice);
}


void StreamingClient::_onLocationDeletedNotice(const LocationDeletedNotice& notice)
{
    _locationDeletedNoticeChannel.send(notice);
}


void StreamingClient::_onLimitNotice(const LimitNotice& notice)
{
    _limitNoticeChannel.send(notice);
}


void StreamingClient::_onStatusWithheldNotice(const StatusWithheldNotice& notice)
{
    _statusWithheldNoticeChannel.send(notice);
}


void StreamingClient::_onUserWitheldNotice(const UserWithheldNotice& notice)
{
    _userWithheldNoticeChannel.send(notice);
}


void StreamingClient::_onDisconnectNotice(const DisconnectNotice& notice)
{
    _disconnectNoticeChannel.send(notice);
}


void StreamingClient::_onStallWarning(const StallWarning& notice)
{
    _stallwarningChannel.send(notice);
}


void StreamingClient::_onException(const std::exception& exc)
{
    _exceptionChannel.send(exc);
}


void StreamingClient::_onMessage(const ofJson& message)
{
    _messageChannel.send(message);
}

    
} } // namespace ofx::Twitter
