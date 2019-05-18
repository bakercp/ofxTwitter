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
    BaseClient(credentials),
    IO::PollingThread(std::bind(&BaseSearchClient::_run, this))
{
}


BaseSearchClient::~BaseSearchClient()
{
}


//void BaseSearchClient::setCredentialsFromFile(const std::filesystem::path& credentialsPath)
//{
//    setCredentials(HTTP::OAuth10Credentials::fromFile(credentialsPath));
//}
//
//
//void BaseSearchClient::setCredentialsFromJson(const ofJson& credentials)
//{
//    setCredentials(HTTP::OAuth10Credentials::fromJSON(credentials));
//}
//
//
//void BaseSearchClient::setCredentials(const HTTP::OAuth10Credentials& credentials)
//{
//    std::unique_lock<std::mutex> lock(mutex);
//    _credentials = credentials;
//}


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


//HTTP::OAuth10Credentials BaseSearchClient::getCredentials() const
//{
//    std::unique_lock<std::mutex> lock(mutex);
//    return _credentials;
//}


void BaseSearchClient::search(const std::string& query)
{
    search(SearchQuery(query));
}


void BaseSearchClient::search(const SearchQuery& query)
{
    stopAndJoin();
    _searchQuery = std::make_unique<SearchQuery>(query);
    _onStart(query);
    start();
}


RateLimit BaseSearchClient::rateLimit() const
{
    std::unique_lock<std::mutex> lock(mutex);
    return _rateLimit;
}


const SearchQuery* BaseSearchClient::searchQuery() const
{
    return _searchQuery.get();
}


void BaseSearchClient::_run()
{
    HTTP::ClientSessionSettings sessionSettings;
    sessionSettings.addDefaultHeader("X-User-Agent", USER_AGENT);
    sessionSettings.setUserAgent(USER_AGENT);
    _client.context().setClientSessionSettings(sessionSettings);
    _client.setCredentials(_credentials);

    int64_t sinceId = _searchQuery->getSinceId();

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
            int64_t requestedSinceId = _searchQuery->getSinceId();
            int64_t sinceId = requestedSinceId;

            for (auto& status: response.statuses())
            {
                if (status.id() > sinceId)
                {
                    sinceId = status.id();
                }

                // This takes care of situations were there are less than
                // max-count and all are returned.
                if (status.id() > requestedSinceId)
                {
                    _onStatus(status);
                }
            }

            // Here we increment the sinceId
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
        ofLogError("BaseSearchClient::_run: Poco::Exception: ") << exc.displayText();
        _onException(exc);
    }
    catch (const std::exception& exc)
    {
        Poco::Exception ex(exc.what());
        ofLogError("BaseSearchClient::_run: std::exception: ") << ex.displayText();
        _onException(exc);
    }
    catch (...)
    {
        Poco::Exception exc("Unknown exception.");
        ofLogError("BaseSearchClient::_run") << exc.displayText();
        _onException(exc);
    }
}


SearchClient::SearchClient(bool autoEventSync):
    SearchClient(HTTP::OAuth10Credentials(), autoEventSync)
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
}


void SearchClient::_update(ofEventArgs&)
{
    syncEvents();
}


void SearchClient::_exit(ofEventArgs&)
{
    syncEvents();
}


void SearchClient::_onStart(const SearchQuery& query)
{
    onStart.notify(this, query);
}


void SearchClient::_onStop()
{
    onStop.notify(this);
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
