//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/Twitter/StreamingClient.h"
#include "ofx/HTTP/HTTPUtils.h"
#include "ofx/IO/ByteBufferUtils.h"
#include "ofx/Twitter/User.h"
#include "ofx/Twitter/SampleQuery.h"


namespace ofx {
namespace Twitter {


const uint64_t StreamingClient::TIMEOUT = 90000;
const std::string StreamingClient::USER_AGENT = "ofxTwitter (compatible; Client/1.0 +https://github.com/bakercp/ofxTwitter)";


StreamingClient::StreamingClient():
    StreamingClient(HTTP::OAuth10Credentials())
{
}


StreamingClient::StreamingClient(const HTTP::OAuth10Credentials& credentials):
    _client(credentials),
    _isConnected(false),
    _streamType(StreamType::NONE),
    _exitListener(ofEvents().exit.newListener(this, &StreamingClient::exit)),
    _updateListener(ofEvents().update.newListener(this, &StreamingClient::update))

{
    HTTP::ClientSessionSettings sessionSettings;
    sessionSettings.addDefaultHeader("X-User-Agent", USER_AGENT);
    sessionSettings.setUserAgent(USER_AGENT);
    sessionSettings.setTimeout(TIMEOUT * Poco::Timespan::MILLISECONDS);
    _client.context().setClientSessionSettings(sessionSettings);
}

StreamingClient::~StreamingClient()
{
    // N.B. In most cases, IPVideoGrabber::exit() will be called before
    // the program ever makes it into this destructor.
    waitForDisconnect();
    ofLogVerbose("StreamingClient::~StreamingClient") << "Destroyed.";
}

void StreamingClient::update(ofEventArgs& a)
{
    {
        bool v;
        while (_onConnect.tryReceive(v)) onConnect.notify(this);
    }
    {
        bool v;
        while (_onDisconnect.tryReceive(v)) onDisconnect.notify(this);
    }

    {
        Status value;
        while (_onStatus.tryReceive(value)) onStatus.notify(this, value);
    }
    {
        StatusDeletedNotice value;
        while (_onStatusDeletedNotice.tryReceive(value)) onStatusDeletedNotice.notify(this, value);
    }
    {
        LocationDeletedNotice value;
        while (_onLocationDeletedNotice.tryReceive(value)) onLocationDeletedNotice.notify(this, value);
    }
    {
        LimitNotice value;
        while (_onLimitNotice.tryReceive(value)) onLimitNotice.notify(this, value);
    }
    {
        StatusWithheldNotice value;
        while (_onStatusWithheldNotice.tryReceive(value)) onStatusWithheldNotice.notify(this, value);
    }
    {
        UserWithheldNotice value;
        while (_onUserWitheldNotice.tryReceive(value)) onUserWitheldNotice.notify(this, value);
    }
    {
        DisconnectNotice value;
        while (_onDisconnectNotice.tryReceive(value)) onDisconnectNotice.notify(this, value);
    }
    {
        StallWarning value;
        while (_onStallWarning.tryReceive(value)) onStallWarning.notify(this, value);
    }
    {
        std::exception value;
        while (_onException.tryReceive(value)) onException.notify(this, value);
    }
    {
        ofJson value;
        while (_onMessage.tryReceive(value)) onMessage.notify(this, value);
    }

    uint64_t now = ofGetElapsedTimeMillis();

    // Disconnect if no new message has arrived and the socket hasn't timed out.
    if (_isConnected && now > (_lastMessage + TIMEOUT))
    {
        Poco::TimeoutException exc("No data received in " + std::to_string(TIMEOUT) + " ms. Disconnecting.");
        onException.notify(this, exc);
        disconnect();
    }
}

void StreamingClient::exit(ofEventArgs& a)
{
    ofLogVerbose("StreamingClient::exit") << "exit() called. Cleaning up and exiting.";
    waitForDisconnect();
}


void StreamingClient::waitForDisconnect()
{
    ofLogWarning("StreamingClient::waitForDisconnect")  << "Waiting for disconnect ... ";

    disconnect();

    try
    {
        _thread.join();
    }
    catch (const std::exception& exc)
    {
        ofLogVerbose("IPVideoGrabber::waitForDisconnect")  << "Joining failed: " << exc.what();
    }
}


void StreamingClient::disconnect()
{
    if (_isConnected)
    {
        _isConnected = false;

        if (_client.context().clientSession())
        {
            try
            {
                _client.context().clientSession()->abort();
            }
            catch (const Poco::Exception& exc)
            {
                ofLogWarning("StreamingClient::disconnect")  << exc.displayText();
            }
        }
    }
    else
    {
        ofLogWarning("StreamingClient::disconnect")  << "Not connected. Connect first.";
    }
}


void StreamingClient::close()
{
    disconnect();
}


bool StreamingClient::isConnected() const
{
    return _isConnected;
}


void StreamingClient::setCredentialsFromFile(const std::filesystem::path& credentialsPath)
{
    setCredentials(HTTP::OAuth10Credentials::fromFile("credentials.json"));
}


void StreamingClient::setCredentialsFromJson(const ofJson& credentials)
{
    setCredentials(HTTP::OAuth10Credentials::fromJSON(credentials));
}


void StreamingClient::setCredentials(const HTTP::OAuth10Credentials& credentials)
{
    _client.setCredentials(credentials);
}


StreamingClient::StreamType StreamingClient::streamType() const
{
    return _streamType;
}


void StreamingClient::sample()
{
    sample(SampleQuery());
}


void StreamingClient::sample(const SampleQuery& query)
{
    if (!_isConnected)
    {
        waitForDisconnect();
        _thread = std::thread(&StreamingClient::_stream,
                              this,
                              StreamType::SAMPLE, query);
    }
    else
    {
        ofLogWarning("StreamingClient::sample")  << "Already connected.  Disconnect first.";
    }
}


void StreamingClient::filter(std::vector<std::string> track,
                             std::vector<std::string> follow,
                             std::vector<Geo::CoordinateBounds> locations)
{
    FilterQuery query;
    query.setTracks(track);
    query.setFollows(follow);
    query.setLocations(locations);
    filter(query);
}


void StreamingClient::filter(const FilterQuery& query)
{
    if (!_isConnected)
    {
        waitForDisconnect();
        _thread = std::thread(&StreamingClient::_stream,
                              this,
                              StreamType::FILTER,
                              query);
    }
    else
    {
        ofLogWarning("StreamingClient::sample")  << "Already connected. Disconnect first.";
    }
}


void StreamingClient::_stream(StreamType streamType,
                              const Poco::Net::NameValueCollection& parameters)
{
    try
    {
        std::string url;
        std::string httpMethod;
        std::string httpVersion = Poco::Net::HTTPMessage::HTTP_1_1;

        if (streamType == StreamType::NONE)
        {
            ofLogError("StreamingClient::_stream") << "Invalid stream type NONE.";
            return;
        }
        if (streamType == StreamType::FILTER)
        {
            httpMethod = Poco::Net::HTTPRequest::HTTP_POST;
            url = FilterQuery::RESOURCE_URL;
        }
        else if (streamType == StreamType::SAMPLE)
        {
            httpMethod = Poco::Net::HTTPRequest::HTTP_GET;
            url = SampleQuery::RESOURCE_URL;
        }
        else if (streamType == StreamType::FIREHOSE)
        {
            httpMethod = Poco::Net::HTTPRequest::HTTP_GET;
            url = FirehoseQuery::RESOURCE_URL;
        }

        _lastMessage = ofGetElapsedTimeMillis();
        _isConnected = true;
        _onConnect.send(_isConnected);
        _streamType = streamType;

        HTTP::FormRequest request(httpMethod, url, httpVersion);

        request.addFormFields(parameters);

        auto response = _client.execute(request);

        if (!response->isSuccess())
        {
            ofBuffer result = response->buffer();
        }
        else
        {
            std::istream& istr = response->stream();
            std::string line;

            while (_isConnected && std::getline(istr, line))
            {
                _lastMessage = ofGetElapsedTimeMillis();

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
                            _onMessage.send(json);
                        }


                        if (json.find(StatusDeletedNotice::JSON_KEY) != json.end())
                        {
                            _onStatusDeletedNotice.send(StatusDeletedNotice::fromJSON(json[StatusDeletedNotice::JSON_KEY]));
                        }
                        else if (json.find(LocationDeletedNotice::JSON_KEY) != json.end())
                        {
                            _onLocationDeletedNotice.send(LocationDeletedNotice::fromJSON(json[LocationDeletedNotice::JSON_KEY]));
                        }
                        else if (json.find(LimitNotice::JSON_KEY) != json.end())
                        {
                            _onLimitNotice.send(LimitNotice::fromJSON(json[LimitNotice::JSON_KEY]));
                        }
                        else if (json.find(StatusWithheldNotice::JSON_KEY) != json.end())
                        {
                            _onStatusWithheldNotice.send(StatusWithheldNotice::fromJSON(json[StatusWithheldNotice::JSON_KEY]));
                        }
                        else if (json.find(UserWithheldNotice::JSON_KEY) != json.end())
                        {
                            _onUserWitheldNotice.send(UserWithheldNotice::fromJSON(json[UserWithheldNotice::JSON_KEY]));
                        }
                        else if (json.find(DisconnectNotice::JSON_KEY) != json.end())
                        {
                            _onDisconnectNotice.send(DisconnectNotice::fromJSON(json[DisconnectNotice::JSON_KEY]));
                        }
                        else if (json.find(StallWarning::JSON_KEY) != json.end())
                        {
                            _onStallWarning.send(StallWarning::fromJSON(json[StallWarning::JSON_KEY]));
                        }
                        else if (json.find("text") != json.end())
                        {
                            _onStatus.send(Status::fromJSON(json));
                        }
                    }
                    catch (const std::exception& exc)
                    {
                        _onException.send(exc);
                    }
                }
            }
        }
    }
    catch (const Poco::Exception& exc)
    {
        _onException.send(exc);
    }
    catch (const std::exception& exc)
    {
        _onException.send(exc);
    }
    catch (...)
    {
        Poco::Exception exc("Unknown exception.");
        _onException.send(exc);
    }

    _isConnected = false;
    _onDisconnect.send(_isConnected);
    _streamType = StreamType::NONE;

}

    
} } // namespace ofx::Twitter
