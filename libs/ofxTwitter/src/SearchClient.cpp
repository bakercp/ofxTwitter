//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/Twitter/SearchClient.h"
#include "ofx/HTTP/HTTPUtils.h"
#include "ofx/HTTP/GetRequest.h"
#include "ofx/HTTP/PostRequest.h"
#include "ofx/IO/ByteBufferUtils.h"
#include "ofx/Twitter/User.h"


namespace ofx {
namespace Twitter {


const std::string BaseSearchClient::USER_AGENT = "ofxTwitter (compatible; Client/1.0 +https://github.com/bakercp/ofxTwitter)";


BaseSearchClient::BaseSearchClient():
    BaseSearchClient(HTTP::OAuth10Credentials())
{
}


BaseSearchClient::BaseSearchClient(const HTTP::OAuth10Credentials& credentials):
    IO::PollingThread(std::bind(&BaseSearchClient::_run, this)),
    _credentials(credentials)
{
}


BaseSearchClient::~BaseSearchClient()
{
}


void BaseSearchClient::setCredentialsFromFile(const std::filesystem::path& credentialsPath)
{
    setCredentials(HTTP::OAuth10Credentials::fromFile(credentialsPath));
}


void BaseSearchClient::setCredentialsFromJson(const ofJson& credentials)
{
    setCredentials(HTTP::OAuth10Credentials::fromJSON(credentials));
}


void BaseSearchClient::setCredentials(const HTTP::OAuth10Credentials& credentials)
{
    std::unique_lock<std::mutex> lock(mutex);
    _credentials = credentials;
}


void BaseSearchClient::onStopRequested()
{
    if (_client.context().clientSession())
    {
        try
        {
            _client.context().clientSession()->abort();
        }
        catch (const Poco::Exception& exc)
        {
            ofLogWarning("BaseSearchClient::disconnect")  << exc.displayText();
        }
    }
}


HTTP::OAuth10Credentials BaseSearchClient::getCredentials() const
{
    std::unique_lock<std::mutex> lock(mutex);
    return _credentials;
}


void BaseSearchClient::search(const std::string& query)
{
    search(SearchQuery(query));
}


void BaseSearchClient::search(const SearchQuery& query)
{
    stopAndJoin();
    _searchQuery = std::make_unique<SearchQuery>(query);
    start();
}


RateLimit BaseSearchClient::rateLimit() const
{
    std::unique_lock<std::mutex> lock(mutex);
    return _rateLimit;
}


void BaseSearchClient::_run()
{
    HTTP::ClientSessionSettings sessionSettings;
    sessionSettings.addDefaultHeader("X-User-Agent", USER_AGENT);
    sessionSettings.setUserAgent(USER_AGENT);
    _client.context().setClientSessionSettings(sessionSettings);
    _client.setCredentials(_credentials);

    try
    {
        HTTP::GetRequest request(SearchQuery::RESOURCE_URL);
        request.addFormFields(*_searchQuery);

        auto httpResponse = _client.execute(request);

        mutex.lock();
        _rateLimit = RateLimit::fromHeaders(*httpResponse);
        mutex.unlock();

        ofJson responseJson = httpResponse->json();

        SearchResponse response = SearchResponse::fromJSON(responseJson);

        if (response.errors().empty())
        {
            int64_t sinceId = _searchQuery->getSinceId();

            for (auto& status: response.statuses())
            {
                _onStatus(status);
                sinceId = std::max(sinceId, status.id());
            }

            _searchQuery->setSinceId(sinceId);
        }
        else
        {
            for (auto& error: response.errors())
            {
                _onError(error);
            }
        }

        _onMessage(responseJson);
    }
    catch (const Poco::Exception& exc)
    {
        ofLogError("BaseSearchClient::_run") << exc.displayText();
        _onException(Poco::Exception(exc));
    }
    catch (const std::exception& exc)
    {
        ofLogError("BaseSearchClient::_run") << exc.what();
        _onException(std::exception(exc));
    }
    catch (...)
    {
        Poco::Exception exc("Unknown exception.");
        ofLogError("BaseSearchClient::_run") << exc.displayText();
        _onException(exc);
    }
}


SearchClient::SearchClient(bool autoEventSync):
    SearchClient(HTTP::OAuth10Credentials())
{
}


SearchClient::SearchClient(const HTTP::OAuth10Credentials& credentials,
                                 bool autoEventSync):
    BaseSearchClient(credentials)
{
    setAutoEventSync(autoEventSync);
}


SearchClient::~SearchClient()
{
}


void SearchClient::setAutoEventSync(bool value)
{
    if (value)
    {
        _updateListener = ofEvents().update.newListener(this, &SearchClient::_update);
        _exitListener = ofEvents().exit.newListener(this, &SearchClient::_exit);
    }
    else
    {
        _updateListener.unsubscribe();
        _exitListener.unsubscribe();
    }

    _autoEventSync = value;
}


void SearchClient::syncEvents()
{
    for (const auto& v: _statusChannel.tryReceiveAll()) onStatus.notify(this, v);
    for (const auto& v: _errorChannel.tryReceiveAll()) onError.notify(this, v);
    for (const auto& v: _exceptionChannel.tryReceiveAll()) onException.notify(this, v);
    for (const auto& v: _messageChannel.tryReceiveAll()) onMessage.notify(this, v);

//    uint64_t now = ofGetElapsedTimeMillis();
//
//    // Disconnect if no new message has arrived and the socket hasn't timed out.
//    if (isRunning() && now > (_lastMessageTime + TIMEOUT))
//    {
//        Poco::TimeoutException exc("No data received in " + std::to_string(TIMEOUT) + " ms. Disconnecting.");
//        onException.notify(this, exc);
//        stop();
//    }
}


void SearchClient::_update(ofEventArgs& args)
{
    syncEvents();
}


void SearchClient::_exit(ofEventArgs& args)
{
    syncEvents();
}


void SearchClient::_onStatus(const Status& status)
{
    _statusChannel.send(status);
}


void SearchClient::_onError(const Error& error)
{
    _errorChannel.send(error);
}


void SearchClient::_onException(const std::exception& exc)
{
    _exceptionChannel.send(std::exception(exc));
}


void SearchClient::_onMessage(const ofJson& message)
{
    _messageChannel.send(message);
}

    
} } // namespace ofx::Twitter
