//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include "ofx/Geo/CoordinateBounds.h"
#include "ofx/Twitter/StreamingQuery.h"


namespace ofx {
namespace Twitter {


/// \brief Parameters needed to request Twitter Streams.
/// \sa https://dev.twitter.com/streaming/overview/request-parameters
class BaseFilterQuery: public StreamingQuery
{
public:
    /// \brief Destroy the BaseFilterQuery.
    virtual ~BaseFilterQuery();

    /// \brief A phrase to track.
    ///
    /// A phrase may be one or more terms separated by spaces, and a phrase will
    /// match if all of the terms in the phrase are present in the Tweet,
    /// regardless of order and ignoring case. By this model, you can think of
    /// commas as logical ORs, while spaces are equivalent to logical ANDs (e.g.
    /// ‘the twitter’ is the AND twitter, and ‘the,twitter’ is the OR twitter).
    ///
    /// \sa https://dev.twitter.com/streaming/overview/request-parameters#track
    /// \param track A single phrase to track.
    void setTrack(const std::string& track);

    /// \brief A list of phrases to track.
    ///
    /// A phrase may be one or more terms separated by spaces, and a phrase will
    /// match if all of the terms in the phrase are present in the Tweet,
    /// regardless of order and ignoring case. By this model, you can think of
    /// commas as logical ORs, while spaces are equivalent to logical ANDs (e.g.
    /// ‘the twitter’ is the AND twitter, and ‘the,twitter’ is the OR twitter).
    ///
    /// Before sending, each item in the list will be seprated by a comma.
    ///
    /// \sa https://dev.twitter.com/streaming/overview/request-parameters#track
    /// \param tracks The list of phrases to track.
    void setTracks(const std::vector<std::string>& tracks);

    /// \brief A set of bounding boxes to filter Tweets.
    ///
    /// Only geolocated Tweets falling within the requested bounding boxes will
    /// be included—unlike the Search API, the user’s location field is not used
    /// to filter tweets.
    ///
    /// \sa https://dev.twitter.com/streaming/overview/request-parameters#locations
    /// \param location The coordinate bounds to track.
    void setLocation(const Geo::CoordinateBounds& location);

    /// \brief A set of bounding boxes to filter Tweets.
    ///
    /// Only geolocated Tweets falling within the requested bounding boxes will
    /// be included—unlike the Search API, the user’s location field is not used
    /// to filter tweets.
    ///
    /// \sa https://dev.twitter.com/streaming/overview/request-parameters#locations
    /// \param locations The list of coordinate bounds to track.
    void setLocations(const std::vector<Geo::CoordinateBounds>& locations);

    /// \brief Elevated access clients use count to backfill missed messages.
    /// \sa https://dev.twitter.com/streaming/overview/request-parameters#count
    void setCount(int count);

};


/// \brief Parameters for a streaming filter request.
/// \sa https://dev.twitter.com/streaming/reference/post/statuses/filter
class FilterQuery: public BaseFilterQuery
{
public:
    /// \brief Destroy the FilterQuery.
    virtual ~FilterQuery();

    /// \brief A single user to track.
    ///
    /// A user ID, indicating the users whose Tweets should be delivered on the
    /// stream. Following protected users is not supported. For each user
    /// specified, the stream will contain:
    ///
    /// - Tweets created by the user.
    /// - Tweets which are retweeted by the user.
    /// - Replies to any Tweet created by the user.
    /// - Retweets of any Tweet created by the user.
    /// - Manual replies, created without pressing a reply button (e.g.
    ///     "@twitterapi I agree").
    ///
    /// The stream will not contain:
    ///
    /// - Tweets mentioning the user (e.g. "Hello @twitterapi!").
    /// - Manual Retweets created without pressing a Retweet button (e.g.
    ///     "RT @twitterapi The API is great").
    /// - Tweets by protected users.
    ///
    /// \sa https://dev.twitter.com/streaming/overview/request-parameters#follow
    /// \param follow A single user to track.
    void setFollow(const std::string& follow);

    /// \brief A list of users to track.
    ///
    /// A user ID, indicating the users whose Tweets should be delivered on the
    /// stream. Following protected users is not supported. For each user
    /// specified, the stream will contain:
    ///
    /// - Tweets created by the user.
    /// - Tweets which are retweeted by the user.
    /// - Replies to any Tweet created by the user.
    /// - Retweets of any Tweet created by the user.
    /// - Manual replies, created without pressing a reply button (e.g.
    ///     "@twitterapi I agree").
    ///
    /// The stream will not contain:
    ///
    /// - Tweets mentioning the user (e.g. "Hello @twitterapi!").
    /// - Manual Retweets created without pressing a Retweet button (e.g.
    ///     "RT @twitterapi The API is great").
    /// - Tweets by protected users.
    ///
    /// Listed users will be seperated by commas before sending.
    ///
    /// \sa https://dev.twitter.com/streaming/overview/request-parameters#follow
    /// \param follows A list of users to track.
    void setFollows(const std::vector<std::string>& follows);

    /// \brief The endpoint.
    static const std::string RESOURCE_URL;

};



/// \brief Parameters needed to request User and Site Streams.
/// \sa https://dev.twitter.com/streaming/overview/request-parameters
class UserFilterQuery: public BaseFilterQuery
{
public:
    /// \brief Control the messages delivered to User and Site Streams clients.
    /// \sa https://dev.twitter.com/streaming/overview/request-parameters#with
    enum class With
    {
        DEFAULT,
        USERS,
        FOLLOWINGS
    };

    /// \brief Destroy the UserFilterQuery.
    virtual ~UserFilterQuery();

    /// \brief Determine if replies should be returned.
    /// \sa https://dev.twitter.com/streaming/overview/request-parameters#replies
    /// \param replies True if replies should be returned.
    void setReplies(bool replies);

    /// \brief Control the messages delivered to User and Site Streams clients.
    /// \sa https://dev.twitter.com/streaming/overview/request-parameters#with
    void setWith(With with);

    /// \brief The endpoint.
    static const std::string RESOURCE_URL;

};


// TODO: SiteFilterQuery


} } // namespace ofx::Twitter
