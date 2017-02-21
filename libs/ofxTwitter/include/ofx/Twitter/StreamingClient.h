//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//



#pragma once


#include "Poco/Net/NameValueCollection.h"
#include "ofThreadChannel.h"
#include "ofx/HTTP/OAuth10HTTPClient.h"
#include "ofx/HTTP/GetRequest.h"
#include "ofx/HTTP/PostRequest.h"
#include "ofx/Geo/CoordinateBounds.h"
#include "ofx/Twitter/FilterQuery.h"
#include "ofx/Twitter/FirehoseQuery.h"
#include "ofx/Twitter/Notices.h"
#include "ofx/Twitter/Status.h"
#include "ofx/Twitter/SampleQuery.h"


namespace ofx {
namespace Twitter {


class SampleQuery;


/// \brief Twitter Streaming API client.
class StreamingClient
{
public:
    /// \brief The types of streams available.
    /// \note Some (e.g. FIREHOSE) may require additional permissions from Twitter.
    enum class StreamType
    {
        /// \brief The client is disconnected.
        NONE,
        /// \brief A filter stream.
        FILTER,
        /// \brief A sample stream.
        SAMPLE,
        /// \brief A firehose stream.
        FIREHOSE,
    };

    /// \brief Create an unconnected StreamingClient with no credentials.
    StreamingClient();

    /// \brief Create an unconnected StreamingClient with given credentials.
    /// \param credentials The OAuth 1.0 credentials to use.
    StreamingClient(const HTTP::OAuth10Credentials& credentials);

    /// \brief Destroy the StreamingClient.
    virtual ~StreamingClient();

    /// \brief Disconnect and block until disconnected.
    void waitForDisconnect();

    /// \brief Disconnect, if currently connected, will not block.
    void disconnect();

    /// \brief Close the current connection, will not block.
    void close();

    /// \returns true if the client is currently connected.
    bool isConnected() const;

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


//    std::string user(WithParam with,
//                    Replies replies,
//                    std::vector<std::string> follow,
//                    std::vector<std::string> track,
//                    std::vector<Geo::CoordinateBounds> locations);
//                    // stringify_friend_ids=false
//
//
//    /// https://sitestream.twitter.com/1.1/site.json
//    /// https://dev.twitter.com/streaming/sitestreams
//    std::string site(WithParam with,
//                    Replies replies,
//                    std::vector<std::string> follow);
//                    // stringify_friend_ids=false
//                    // delimited=length
//                    // stall_warnings=true
//
//    /// https://stream.twitter.com/1.1/statuses/firehose.json
//    std::string firehose(int count);
//    // delimited=length
//    // stall_warnings=true

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

    /// \brief Called for all messages, including those that are parsed.
    ///
    /// This call back allows users to extract any data that is unparsed due
    /// to changes in the API.
    ofEvent<const ofJson> onMessage;

    /// \brief The StreamingClient timeout.
    ///
    /// This value is set to 90000 milliseconds, as recommended by the
    /// connecting guide.
    ///
    /// \sa https://dev.twitter.com/streaming/overview/connecting
    static const uint64_t TIMEOUT;

    /// \brief The StreamingClient user agent.
    ///
    /// Both the `User-Agent` and `X-User-Agent` are set to this value.
    ///
    /// The default value is
    static const std::string USER_AGENT;

private:
    /// \brief Update callback from the main thread.
    ///
    /// This is used to synchronize message delivery.
    ///
    /// \param evt The event passed from the main loop.
    void update(ofEventArgs& evt);

    /// \brief Exit callback from the main thread.
    ///
    /// This is used to make sure the thread is shut down correctly.
    ///
    /// \param evt The event passed from the main loop.
    void exit(ofEventArgs& evt);

    /// \brief Create the stream.
    /// \param streamType the type of stream to initialize.
    /// \param parameters The parameters to start the stream with.
    void _stream(StreamType streamType,
                 const Poco::Net::NameValueCollection& parameters);

    /// \brief The OAuth 1.0 client.
    HTTP::OAuth10HTTPClient _client;

    ofThreadChannel<bool> _onConnect;
    ofThreadChannel<bool> _onDisconnect;
    ofThreadChannel<Status> _onStatus;
    ofThreadChannel<StatusDeletedNotice> _onStatusDeletedNotice;
    ofThreadChannel<LocationDeletedNotice> _onLocationDeletedNotice;
    ofThreadChannel<LimitNotice> _onLimitNotice;
    ofThreadChannel<StatusWithheldNotice> _onStatusWithheldNotice;
    ofThreadChannel<UserWithheldNotice> _onUserWitheldNotice;
    ofThreadChannel<DisconnectNotice> _onDisconnectNotice;
    ofThreadChannel<StallWarning> _onStallWarning;
    ofThreadChannel<std::exception> _onException;
    ofThreadChannel<ofJson> _onMessage;

    ofEventListener _exitListener;
    ofEventListener _updateListener;

    std::thread _thread;
    std::atomic<bool> _isConnected;
    std::atomic<StreamType> _streamType;

    uint64_t _lastMessage = 0;

    mutable std::mutex mutex;

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
    onLocationDeletedNotice.remove(listener, &ListenerClass::onLocationDeletedNotice, priority);
    onLimitNotice.remove(listener, &ListenerClass::onLimitNotice, priority);
    onStatusWithheldNotice.remove(listener, &ListenerClass::onStatusWithheldNotice, priority);
    onUserWitheldNotice.remove(listener, &ListenerClass::onUserWitheldNotice, priority);
    onDisconnectNotice.remove(listener, &ListenerClass::onDisconnectNotice, priority);
    onStallWarning.remove(listener, &ListenerClass::onStallWarning, priority);
    onException.remove(listener, &ListenerClass::onException, priority);
    onMessage.remove(listener, &ListenerClass::onMessage, priority);
}


} } // namespace ofx::Twitter
