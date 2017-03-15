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


/// \brief Twitter Streaming API client.
class BaseStreamingClient: public IO::Thread
{
public:
    /// \brief The types of streams available.
    /// \note Some (e.g. USER) may require additional permissions from Twitter.
    enum class StreamType
    {
        /// \brief The client is disconnected.
        NONE,
        /// \brief A filter stream.
        FILTER,
        /// \brief A sample stream.
        SAMPLE,
        /// \brief A user stream.
        USER,
        /// \brief A site stream.
        // SITE
    };

    /// \brief Create a default BaseStreamingClient.
    BaseStreamingClient();

    /// \brief Create a default BaseStreamingClient.
    /// \param credentials The OAuth 1.0 credentials to use.
    BaseStreamingClient(const HTTP::OAuth10Credentials& credentials);

    /// \brief Destroy the BaseStreamingClient.
    virtual ~BaseStreamingClient();

    /// \brief Create an unconnected BaseStreamingClient with given parameters.
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

    /// \returns the current stream type, or NONE if disconnected.
    StreamType streamType() const;

    /// \brief Returns a small random sample of all public statuses.
    ///
    /// The Tweets returned by the default access level are the same, so if two
    /// different clients connect to this endpoint, they will see the same Tweets.
    ///
    /// \sa https://dev.twitter.com/streaming/reference/get/statuses/sample
    void sample();

    /// \brief Returns a small random sample of all public statuses.
    ///
    /// The Tweets returned by the default access level are the same, so if two
    /// different clients connect to this endpoint, they will see the same Tweets.
    ///
    /// \sa https://dev.twitter.com/streaming/reference/get/statuses/sample
    ///
    /// \param query The sample query.
    void sample(const SampleQuery& query);

    /// \brief Returns public statuses that match one or more filter predicates.
    ///
    /// Multiple parameters may be specified which allows most clients to use a
    /// single connection to the Streaming API.
    ///
    /// For more about tracks:
    /// https://dev.twitter.com/streaming/overview/request-parameters#track
    ///
    /// \sa https://dev.twitter.com/streaming/reference/post/statuses/filter
    void filter(std::vector<std::string> track,
                std::vector<std::string> follow = {},
                std::vector<Geo::CoordinateBounds> locations = {});

    /// \brief Returns public statuses that match one or more filter predicates.
    ///
    /// Multiple parameters may be specified which allows most clients to use a
    /// single connection to the Streaming API.
    ///
    /// \sa https://dev.twitter.com/streaming/reference/post/statuses/filter
    void filter(const FilterQuery& query);

    void user(const UserFilterQuery& query);

    /// \returns the current stream parameters.
    Poco::Net::NameValueCollection parameters() const;

    /// \brief The BaseStreamingClient timeout.
    ///
    /// This value is set to 90000 milliseconds, as recommended by the
    /// connecting guide.
    ///
    /// \sa https://dev.twitter.com/streaming/overview/connecting
    static const uint64_t TIMEOUT;

    /// \brief The BaseStreamingClient user agent.
    ///
    /// Both the `User-Agent` and `X-User-Agent` are set to this value.
    ///
    /// The default value is
    static const std::string USER_AGENT;

protected:
    virtual void onStopRequested() override;

    virtual void _onConnect() = 0;
    virtual void _onDisconnect() = 0;
    virtual void _onStatus(const Status& status) = 0;
    virtual void _onStatusDeletedNotice(const StatusDeletedNotice& notice) = 0;
    virtual void _onLocationDeletedNotice(const LocationDeletedNotice& notice) = 0;
    virtual void _onLimitNotice(const LimitNotice& notice) = 0;
    virtual void _onStatusWithheldNotice(const StatusWithheldNotice& notice) = 0;
    virtual void _onUserWitheldNotice(const UserWithheldNotice& notice) = 0;
    virtual void _onDisconnectNotice(const DisconnectNotice& notice) = 0;
    virtual void _onStallWarning(const StallWarning& notice) = 0;
    virtual void _onException(const std::exception& exc) = 0;
    virtual void _onMessage(const ofJson& message) = 0;

    uint64_t _lastMessageTime = 0;

private:
    void _run();

    /// \brief The OAuth 1.0 client.
    HTTP::OAuth10HTTPClient _client;

    HTTP::OAuth10Credentials _credentials;

    StreamType _streamType = StreamType::NONE;
    std::string _url;
    std::string _httpMethod;
    Poco::Net::NameValueCollection _parameters;

};


/// \brief An event-driven Twitter Streaming Client.
class StreamingClient: public BaseStreamingClient
{
public:
    /// \brief Create a default StreamingClient.
    /// \param autoEventSync enable auto event sync.
    StreamingClient(bool autoEventSync = true);

    /// \brief Create an unconnected BaseStreamingClient with given credentials.
    /// \param credentials The OAuth 1.0 credentials to use.
    /// \param autoEventSync enable auto event sync.
    StreamingClient(const HTTP::OAuth10Credentials& credentials,
                    bool autoEventSync = true);

    /// \brief Destroy the StreamingClient.
    virtual ~StreamingClient();

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
    /// onConnect(...), onDisconnect(...), onStatus(...),
    /// onStatusDeletedNotice(...), onLocationDeletedNotice(...),
    /// onLimitNotice(...), onStatusWithheldNotice(...),
    /// onUserWitheldNotice(...), onDisconnectNotice(...), onStallWarning(...).
    /// on
    ///
    /// \tparam ListenerClass The lister class to register.
    /// \param listener A pointer to the listener class.
    /// \param priority The listener priority.
    template <class ListenerClass>
    void registerStreamingEvents(ListenerClass* listener,
                                 int priority = OF_EVENT_ORDER_AFTER_APP);

    /// \brief Unregister all event listeners.
    /// \tparam ListenerClass The lister class to uregister.
    /// \param listener A pointer to the listener class.
    /// \param priority The listener priority.
    template <class ListenerClass>
    void unregisterStreamingEvents(ListenerClass* listener,
                                   int priority = OF_EVENT_ORDER_AFTER_APP);

    ofEvent<void> onConnect;
    ofEvent<void> onDisconnect;
    ofEvent<const Status> onStatus;
    ofEvent<const StatusDeletedNotice> onStatusDeletedNotice;
    ofEvent<const LocationDeletedNotice> onLocationDeletedNotice;
    ofEvent<const LimitNotice> onLimitNotice;
    ofEvent<const StatusWithheldNotice> onStatusWithheldNotice;
    ofEvent<const UserWithheldNotice> onUserWitheldNotice;
    ofEvent<const DisconnectNotice> onDisconnectNotice;
    ofEvent<const StallWarning> onStallWarning;
    ofEvent<const std::exception> onException;
    ofEvent<const ofJson> onMessage;

private:
    void _update(ofEventArgs& args);
    void _exit(ofEventArgs& args);

    virtual void _onConnect() override;
    virtual void _onDisconnect() override;
    virtual void _onStatus(const Status& status) override;
    virtual void _onStatusDeletedNotice(const StatusDeletedNotice& notice) override;
    virtual void _onLocationDeletedNotice(const LocationDeletedNotice& notice) override;
    virtual void _onLimitNotice(const LimitNotice& notice) override;
    virtual void _onStatusWithheldNotice(const StatusWithheldNotice& notice) override;
    virtual void _onUserWitheldNotice(const UserWithheldNotice& notice) override;
    virtual void _onDisconnectNotice(const DisconnectNotice& notice) override;
    virtual void _onStallWarning(const StallWarning& notice) override;
    virtual void _onException(const std::exception& exc) override;
    virtual void _onMessage(const ofJson& message) override;

    bool _autoEventSync = true;

    IO::ThreadChannel<ofEventArgs> _connectChannel;
    IO::ThreadChannel<ofEventArgs> _disconnectChannel;
    IO::ThreadChannel<Status> _statusChannel;
    IO::ThreadChannel<StatusDeletedNotice> _statusDeletedNoticeChannel;
    IO::ThreadChannel<LocationDeletedNotice> _locationDeletedNoticeChannel;
    IO::ThreadChannel<LimitNotice> _limitNoticeChannel;
    IO::ThreadChannel<StatusWithheldNotice> _statusWithheldNoticeChannel;
    IO::ThreadChannel<UserWithheldNotice> _userWithheldNoticeChannel;
    IO::ThreadChannel<DisconnectNotice> _disconnectNoticeChannel;
    IO::ThreadChannel<StallWarning> _stallwarningChannel;
    IO::ThreadChannel<std::exception> _exceptionChannel;
    IO::ThreadChannel<ofJson> _messageChannel;

    ofEventListener _updateListener;
    ofEventListener _exitListener;

};


template <class ListenerClass>
void StreamingClient::registerStreamingEvents(ListenerClass* listener,
                                              int priority)
{
    onConnect.add(listener, &ListenerClass::onConnect, priority);
    onDisconnect.add(listener, &ListenerClass::onDisconnect, priority);
    onStatus.add(listener, &ListenerClass::onStatus, priority);
    onStatusDeletedNotice.add(listener, &ListenerClass::onStatusDeletedNotice, priority);
    onLocationDeletedNotice.add(listener, &ListenerClass::onLocationDeletedNotice, priority);
    onLimitNotice.add(listener, &ListenerClass::onLimitNotice, priority);
    onStatusWithheldNotice.add(listener, &ListenerClass::onStatusWithheldNotice, priority);
    onUserWitheldNotice.add(listener, &ListenerClass::onUserWitheldNotice, priority);
    onDisconnectNotice.add(listener, &ListenerClass::onDisconnectNotice, priority);
    onStallWarning.add(listener, &ListenerClass::onStallWarning, priority);
    onException.add(listener, &ListenerClass::onException, priority);
    onMessage.add(listener, &ListenerClass::onMessage, priority);
}


template <class ListenerClass>
void StreamingClient::unregisterStreamingEvents(ListenerClass* listener,
                                                int priority)
{
    onConnect.remove(listener, &ListenerClass::onConnect, priority);
    onDisconnect.remove(listener, &ListenerClass::onDisconnect, priority);
    onStatus.remove(listener, &ListenerClass::onStatus, priority);
    onStatusDeletedNotice.remove(listener, &ListenerClass::onStatusDeletedNotice, priority);
    onLocationDeletedNotice.remove(listener, &ListenerClass::onLocationDeletedNotices, priority);
    onLimitNotice.remove(listener, &ListenerClass::onLimitNotice, priority);
    onStatusWithheldNotice.remove(listener, &ListenerClass::onStatusWithheldNotice, priority);
    onUserWitheldNotice.remove(listener, &ListenerClass::onUserWitheldNotice, priority);
    onDisconnectNotice.remove(listener, &ListenerClass::onDisconnectNotice, priority);
    onStallWarning.remove(listener, &ListenerClass::onStallWarning, priority);
    onException.remove(listener, &ListenerClass::onException, priority);
    onMessage.remove(listener, &ListenerClass::onMessage, priority);
}



} } // namespace ofx::Twitter
