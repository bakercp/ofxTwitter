//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once

#include <cstdint>
#include "ofJson.h"
//#include "ofx/Twitter/StreamingQuery.h"


namespace ofx {
namespace Twitter {


/// \brief Status deleted notice.
///
/// These messages indicate that a given Tweet has been deleted. Client code
/// must honor these messages by clearing the referenced Tweet from memory and
/// any storage or archive, even in the rare case where a deletion message
/// arrives earlier in the stream that the Tweet it references.
///
/// \sa https://developer.twitter.com/en/docs/tweets/filter-realtime/guides/streaming-message-types
class StatusDeletedNotice
{
public:
    /// \returns the id of the user.
    int64_t userId() const;

    /// \returns the id of the status.
    int64_t statusId() const;

    /// \returns the timestamp of the notice in milliseconds.
    uint64_t timestamp() const;

    /// \returns the original json.
    ofJson json() const;

    static const std::string JSON_KEY;

    static StatusDeletedNotice fromJSON(const ofJson& json);

private:
    /// \brief The id of the user.
    int64_t _userId = -1;

    /// \brief The id of the status.
    int64_t _statusId = -1;

    /// \brief The timestamp of the notice in milliseconds.
    uint64_t _timestamp = 0;

    /// \brief The original json.
    ofJson _json;

};



/// \brief Location deleted notice.
///
/// These messages indicate that geolocated data must be stripped from a range
/// of Tweets. Clients must honor these messages by deleting geocoded data from
/// Tweets which fall before the given status ID and belong to the specified
/// user. These messages may also arrive before a Tweet which falls into the
/// specified range, although this is rare.
///
/// \sa https://developer.twitter.com/en/docs/tweets/filter-realtime/guides/streaming-message-types
class LocationDeletedNotice
{
public:
    /// \returns the id of the user.
    int64_t userId() const;

    /// \returns the id of the status.
    int64_t upToStatusId() const;

    /// \returns the original json.
    ofJson json() const;

    static const std::string JSON_KEY;

    static LocationDeletedNotice fromJSON(const ofJson& json);

private:
    /// \brief The id of the user.
    int64_t _userId = -1;

    /// \brief The id of the status.
    int64_t _upToStatusId = -1;

    /// \returns the original json.
    ofJson _json;

};


/// \brief Track limit notices.
///
/// These messages indicate that a filtered stream has matched more Tweets than
/// its current rate limit allows to be delivered. Limit notices contain a total
/// count of the number of undelivered Tweets since the connection was opened,
/// making them useful for tracking counts of track terms, for example. Note
/// that the counts do not specify which filter predicates undelivered messages
/// matched.
///
// \sa https://developer.twitter.com/en/docs/tweets/filter-realtime/guides/streaming-message-types
class LimitNotice
{
public:
    /// \returns the number missed Tweets for the track.
    uint64_t track() const;

    /// \returns the original json.
    ofJson json() const;

    static const std::string JSON_KEY;

    static LimitNotice fromJSON(const ofJson& json);

private:
    /// \brief The number missed Tweets for the track.
    uint64_t _track = 0;

    /// \brief The original json.
    ofJson _json;

};


/// \brief Status withheld notice.
///
/// These events contain an id field indicating the status ID, a user_id
/// indicating the user, and a collection of withheld_in_countries uppercase
/// two-letter country codes.
///
/// \sa https://developer.twitter.com/en/docs/tweets/filter-realtime/guides/streaming-message-types
class StatusWithheldNotice
{
public:
    /// \returns the id of the user.
    int64_t userId() const;

    /// \returns the id of the user.
    int64_t statusId() const;

    /// \returns the withheld in countries.
    std::vector<std::string> countries() const;

    /// \returns the original json.
    ofJson json() const;

    static const std::string JSON_KEY;

    static StatusWithheldNotice fromJSON(const ofJson& json);

private:
    /// \brief The id of the user.
    int64_t _userId = -1;

    /// \brief The id of the user.
    int64_t _statusId = -1;

    /// \brief Withheld in countries.
    std::vector<std::string> _countries;

    /// \brief The original json.
    ofJson _json;

};


/// \brief User withheld notice.
///
/// These events contain an id field indicating the user ID and a collection of
/// withheld_in_countries uppercase two-letter country codes.
///
/// \sa https://developer.twitter.com/en/docs/tweets/filter-realtime/guides/streaming-message-types
class UserWithheldNotice
{
public:
    /// \returns The id of the user.
    int64_t userId() const;

    /// \returns Withheld in countries.
    std::vector<std::string> countries() const;

    /// \returns the original json.
    ofJson json() const;

    static const std::string JSON_KEY;

    static UserWithheldNotice fromJSON(const ofJson& json);

private:
    /// \brief The id of the user.
    int64_t _userId = -1;

    /// \brief Withheld in countries.
    std::vector<std::string> _countries;

    /// \brief The original json.
    ofJson _json;

};


/// \brief A disconnect notice.
///
/// Streams may be shut down for a variety of reasons. The streaming API will
/// attempt to deliver a message indicating why a stream was closed. Note that
/// if the disconnect was due to network issues or a client reading too slowly,
/// it is possible that this message will not be received.
///
/// \sa https://developer.twitter.com/en/docs/tweets/filter-realtime/guides/streaming-message-types
class DisconnectNotice
{
public:
    /// \returns the disconnect code.
    int64_t code() const;

    /// \returns the stream name.
    std::string streamName() const;

    /// \returns the disconnect reason.
    std::string reason() const;

    /// \returns the original json.
    ofJson json() const;

    static const std::string JSON_KEY;

    static DisconnectNotice fromJSON(const ofJson& json);

private:
    /// \brief The disconnect code.
    int64_t _code = -1;

    /// \brief The stream name.
    std::string _streamName;

    /// \brief The disconnect reason.
    std::string _reason;

    /// \brief the original json.
    ofJson _json;

};



/// \brief Stall warning.
///
/// When connected to a stream using the stall_warnings parameter, you may
/// receive status notices indicating the current health of the connection.
///
/// \sa https://developer.twitter.com/en/docs/tweets/filter-realtime/guides/streaming-message-types
class StallWarning
{
public:
    /// \returns the code.
    std::string code() const;

    /// \returns the message.
    std::string message() const;

    /// \returns the streaming buffer percent full.
    double percentFull() const;

    /// \returns the original json.
    ofJson json() const;

    static const std::string JSON_KEY;

    static StallWarning fromJSON(const ofJson& json);

private:
    /// \brief The code.
    std::string _code;

    /// \brief The message.
    std::string _message;

    /// \brief The streaming buffer percent full.
    double _percentFull = 0;

    /// \brief the original json.
    ofJson _json;

};


} } // namespace ofx::Twitter
