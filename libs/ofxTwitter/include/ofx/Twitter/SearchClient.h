//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include "ofx/HTTP/OAuth10HTTPClient.h"
#include "ofx/IO/PollingThread.h"
#include "ofx/IO/ThreadChannel.h"
#include "ofx/Twitter/Error.h"
#include "ofx/Twitter/Search.h"
#include "ofx/Twitter/Status.h"


namespace ofx {
namespace Twitter {


/// \brief Twitter Streaming API client.
class BaseSearchClient: public IO::PollingThread
{
public:
    /// \brief Create a default BaseSearchClient.
    BaseSearchClient();

    /// \brief Create a default BaseSearchClient.
    /// \param credentials The OAuth 1.0 credentials to use.
    BaseSearchClient(const HTTP::OAuth10Credentials& credentials);

    /// \brief Destroy the BaseSearchClient.
    virtual ~BaseSearchClient();

    /// \brief Create an unconnected BaseSearchClient with given parameters.
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

    /// \brief Execute a basic Twitter Search query.
    ///
    /// Results are returned via callback functions.
    ///
    /// Calling search multiple times will stop and block the current thread
    /// until the new thread has been launched.
    ///
    /// \param query The search string to send.
    void search(const std::string& query);

    /// \brief Execute a basic Twitter Search query.
    ///
    /// Results are returned via callback functions.
    ///
    /// Calling search multiple times will stop and block the current thread
    /// until the new thread has been launched.
    ///
    /// \param query The search string to send.
    void search(const SearchQuery& query);

    /// \returns the last rate limit information if available.
    RateLimit rateLimit() const;

    /// \brief The BaseSearchClient user agent.
    ///
    /// Both the `User-Agent` and `X-User-Agent` are set to this value.
    ///
    /// The default value is
    static const std::string USER_AGENT;

protected:
    virtual void onStopRequested() override;

    virtual void _onStatus(const Status& status) = 0;
    virtual void _onError(const Error& error) = 0;
    virtual void _onException(const std::exception& exc) = 0;
    virtual void _onMessage(const ofJson& message) = 0;

    uint64_t _lastMessageTime = 0;

private:
    void _run();

    RateLimit _rateLimit;

    std::unique_ptr<SearchQuery> _searchQuery;
    SearchResponse _lastSearchResponse;

    HTTP::OAuth10Credentials _credentials;
    HTTP::OAuth10HTTPClient _client;

};


/// \brief An event-driven Twitter Streaming Client.
class SearchClient: public BaseSearchClient
{
public:
    /// \brief Create a default SearchClient.
    /// \param autoEventSync enable auto event sync.
    SearchClient(bool autoEventSync = true);

    /// \brief Create an unconnected BaseSearchClient with given credentials.
    /// \param credentials The OAuth 1.0 credentials to use.
    /// \param autoEventSync enable auto event sync.
    SearchClient(const HTTP::OAuth10Credentials& credentials,
                    bool autoEventSync = true);

    /// \brief Destroy the SearchClient.
    virtual ~SearchClient();

    /// \brief Determine sync If true, events will be triggered from the ofEvents updated loop.
    /// If false, the events will be triggered when eventSync is called.
    /// \param
    void setAutoEventSync(bool value);

    /// \brief Trigger an event sync.
    void syncEvents();

    /// \brief Register all event listeners.
    ///
    /// The listener class must implement the following callbacks:
    ///
    /// onStatus(...), onError(...), onException, onMessage(...) etc.
    ///
    /// \tparam ListenerClass The lister class to register.
    /// \param listener A pointer to the listener class.
    /// \param priority The listener priority.
    template <class ListenerClass>
    void registerSearchEvents(ListenerClass* listener,
                              int priority = OF_EVENT_ORDER_AFTER_APP);

    /// \brief Unregister all event listeners.
    /// \tparam ListenerClass The lister class to uregister.
    /// \param listener A pointer to the listener class.
    /// \param priority The listener priority.
    template <class ListenerClass>
    void unregisterSearchEvents(ListenerClass* listener,
                                int priority = OF_EVENT_ORDER_AFTER_APP);

    ofEvent<const Status> onStatus;
    ofEvent<const Error> onError;
    ofEvent<const std::exception> onException;
    ofEvent<const ofJson> onMessage;

private:
    void _update(ofEventArgs& args);
    void _exit(ofEventArgs& args);

    virtual void _onStatus(const Status& status) override;
    virtual void _onError(const Error& error) override;
    virtual void _onException(const std::exception& exc) override;
    virtual void _onMessage(const ofJson& message) override;

    bool _autoEventSync = true;

    IO::ThreadChannel<Status> _statusChannel;
    IO::ThreadChannel<Error> _errorChannel;
    IO::ThreadChannel<std::exception> _exceptionChannel;
    IO::ThreadChannel<ofJson> _messageChannel;

    ofEventListener _updateListener;
    ofEventListener _exitListener;

};


template <class ListenerClass>
void SearchClient::registerSearchEvents(ListenerClass* listener,
                                        int priority)
{
    onStatus.add(listener, &ListenerClass::onStatus, priority);
    onError.add(listener, &ListenerClass::onError, priority);
    onException.add(listener, &ListenerClass::onException, priority);
    onMessage.add(listener, &ListenerClass::onMessage, priority);
}


template <class ListenerClass>
void SearchClient::unregisterSearchEvents(ListenerClass* listener,
                                          int priority)
{
    onStatus.remove(listener, &ListenerClass::onStatus, priority);
    onError.remove(listener, &ListenerClass::onError, priority);
    onException.remove(listener, &ListenerClass::onException, priority);
    onMessage.remove(listener, &ListenerClass::onMessage, priority);
}



} } // namespace ofx::Twitter
