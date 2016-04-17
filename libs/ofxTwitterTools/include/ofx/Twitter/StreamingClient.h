// =============================================================================
//
// Copyright (c) 2009-2016 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================



#pragma once


#include "Poco/Net/NameValueCollection.h"
#include "ofx/Twitter/BaseClient.h"
#include "ofx/Geo/CoordinateBounds.h"


namespace ofx {
namespace Twitter {


/// \brief Parameters needed to request Twitter Streams.
/// \sa https://dev.twitter.com/streaming/overview/request-parameters
class StreamingRequestParameters: public Poco::Net::NameValueCollection
{
public:
    /// \brief Possible values for the `delimited` request parameter.
    /// \sa https://dev.twitter.com/streaming/overview/request-parameters#delimited
    enum class Delimited
    {
        LENGTH
    };

    /// \brief Possible values for the `filter_level` request parameter.
    /// \sa https://dev.twitter.com/streaming/overview/request-parameters#filter_level
    enum class FilterLevel
    {
        DEFAULT,
        NONE,
        LOW,
        MEDIUM
    };

    /// \brief Destroy the StreamingRequestParameters.
    virtual ~StreamingRequestParameters();

    /// \brief Setting to indicate the Status delimiting strategy.
    ///
    /// Setting this to the string `length` indicates that statuses should be
    /// delimited in the stream, so that clients know how many bytes to read
    /// before the end of the status message. Statuses are represented by a
    /// length, in bytes, a newline, and the status text that is exactly length
    /// bytes. Note that "keep-alive" newlines may be inserted before each
    /// length.
    ///
    /// \sa https://dev.twitter.com/streaming/overview/request-parameters#delimited
    /// \param delimited The delimited parameter.
    void setDelimited(Delimited delimited);

    /// \brief Send stall warnings if the client is in danger of being disconnected.
    ///
    /// Setting this parameter to true will cause periodic messages to be
    /// delivered if the client is in danger of being disconnected. These
    /// messages are only sent when the client is falling behind, and will occur
    /// at a maximum rate of about once every 5 minutes. This parameter is most
    /// appropriate for clients with high-bandwidth connections, such as the
    /// firehose.
    ///
    /// \sa https://dev.twitter.com/streaming/overview/request-parameters#stallwarnings
    /// \param stallWarnings True to enable stall warnings.
    void setStallWarnings(bool stallWarnings);

    /// \brief Limit the number of Tweets included in the stream.
    ///
    /// Setting this parameter to one of NONE, LOW, or MEDIUM will set the
    /// minimum value of the `filter_level` Tweet attribute required to be
    /// included in the stream. The default value is NONE, which includes all
    /// available Tweets.
    ///
    /// When displaying a stream of Tweets to end users (dashboards or live
    /// feeds at a presentation or conference, for example) it is suggested that
    /// you set this value to MEDIUM.
    ///
    /// \sa https://dev.twitter.com/streaming/overview/request-parameters#filter_level
    /// \param filterLevel The filter level to use.
    void setFilterLevel(FilterLevel filterLevel);

    /// \brief Set the language to track.
    ///
    /// Setting this parameter to a comma-separated list of BCP 47 language
    /// identifiers corresponding to any of the languages listed on Twitter's
    /// advanced search page will only return Tweets that have been detected as
    /// being written in the specified languages. For example, connecting with
    /// "en" will only stream Tweets detected to be in the English language.
    ///
    /// \sa https://dev.twitter.com/streaming/overview/request-parameters#language
    /// \sa http://tools.ietf.org/html/bcp47
    /// \param language The language to track.
    void setLanguage(const std::string& language);

    /// \brief Set the list of languages to track.
    ///
    /// Setting this parameter to a comma-separated list of BCP 47 language
    /// identifiers corresponding to any of the languages listed on Twitter's
    /// advanced search page will only return Tweets that have been detected as
    /// being written in the specified languages. For example, connecting with
    /// "en" will only stream Tweets detected to be in the English language.
    ///
    /// \sa https://dev.twitter.com/streaming/overview/request-parameters#language
    /// \sa http://tools.ietf.org/html/bcp47
    /// \param languages The languages to track.
    void setLanguages(const std::vector<std::string>& languages);

    /// \brief Get the parameters as a name-value collection.
    /// \returns The parameters as a name-value collection.
    virtual Poco::Net::NameValueCollection toNameValueCollection() const;

private:
    /// \brief Setting to indicate the Status delimiting strategy.
    /// \sa https://dev.twitter.com/streaming/overview/request-parameters#delimited
    Delimited _delimited = Delimited::LENGTH;

    /// \brief Enable or disable stall warnings.
    /// \sa https://dev.twitter.com/streaming/overview/request-parameters#stallwarnings
    bool _stallWarnings = true;

    /// \brief Limit the number of Tweets included in the stream.
    /// \sa https://dev.twitter.com/streaming/overview/request-parameters#filter_level
    FilterLevel _filterLevel = FilterLevel::DEFAULT;

    /// \brief Set the list of languages to track.
    /// \sa https://dev.twitter.com/streaming/overview/request-parameters#language
    /// \sa http://tools.ietf.org/html/bcp47
    std::vector<std::string> _languages;

};


/// \brief Parameters needed to request Twitter Streams.
/// \sa https://dev.twitter.com/streaming/overview/request-parameters
class BaseFilterStreamingRequestParameters: public StreamingRequestParameters
{
public:
    /// \brief Destroy the StreamingRequestParameters.
    virtual ~BaseFilterStreamingRequestParameters();

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

    virtual Poco::Net::NameValueCollection toNameValueCollection() const override;

private:
    /// \brief A list of phrases to track.
    /// \sa https://dev.twitter.com/streaming/overview/request-parameters#track
    std::vector<std::string> _tracks;

    /// \brief A set of bounding boxes to filter Tweets.
    ///
    /// Only geolocated Tweets falling within the requested bounding boxes will
    /// be included—unlike the Search API, the user’s location field is not used
    /// to filter tweets.
    ///
    /// \sa https://dev.twitter.com/streaming/overview/request-parameters#locations
    std::vector<Geo::CoordinateBounds> _locations;

    /// \brief Elevated access clients use count to backfill missed messages.
    /// \sa https://dev.twitter.com/streaming/overview/request-parameters#count
    int _count = 0;

};


/// \brief Parameters for a streaming filter request.
/// \sa https://dev.twitter.com/streaming/reference/post/statuses/filter
class FilterStreamingRequestParameters: public BaseFilterStreamingRequestParameters
{
public:
    /// \brief Destroy the FilterStreamingRequestParameters.
    virtual ~FilterStreamingRequestParameters();

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

    virtual Poco::Net::NameValueCollection toNameValueCollection() const override;

private:
    /// \brief A list of users to track.
    /// \sa https://dev.twitter.com/streaming/overview/request-parameters#follow
    std::vector<std::string> _follows;


};



/// \brief Parameters needed to request User and Site Streams.
/// \sa https://dev.twitter.com/streaming/overview/request-parameters
class UserStreamingRequestParameters: public BaseFilterStreamingRequestParameters
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

    /// \brief Destroy the UserStreamingRequestParameters.
    virtual ~UserStreamingRequestParameters();

    /// \brief Determine if replies should be returned.
    /// \sa https://dev.twitter.com/streaming/overview/request-parameters#replies
    /// \param replies True if replies should be returned.
    void setReplies(bool replies);

    /// \brief Control the messages delivered to User and Site Streams clients.
    /// \sa https://dev.twitter.com/streaming/overview/request-parameters#with
    void setWith(With with);

    virtual Poco::Net::NameValueCollection toNameValueCollection() const override;

private:
    /// \sa https://dev.twitter.com/streaming/overview/request-parameters#replies
    bool _replies = true;

    /// \brief Control the messages delivered to User and Site Streams clients.
    /// \sa https://dev.twitter.com/streaming/overview/request-parameters#with
    With _with = With::DEFAULT;

    /// \brief Stringify user ids. We set this to false b/c we can parse numbers.
    /// \sa https://dev.twitter.com/streaming/overview/request-parameters#stringify_friend_id
    bool _stringifyUserIds = false;

};


typedef UserStreamingRequestParameters SiteStreamingRequestParameters;


class SampleStreamingRequest: public HTTP::GetRequest
{
public:
    SampleStreamingRequest();
    SampleStreamingRequest(const StreamingRequestParameters& parameters);

    virtual ~SampleStreamingRequest();

    void setParameters(const StreamingRequestParameters& parameters);
    StreamingRequestParameters getParameters() const;

    static const std::string RESOURCE_URL;

private:
    StreamingRequestParameters _parameters;

};


//    class StallMessage
//    {
//        //        {
//        //            "warning":{
//        //                "code":"FALLING_BEHIND",
//        //                "message":"Your connection is falling behind and messages are being queued for delivery to you. Your queue is now over 60% full. You will be disconnected when the queue is full.",
//        //                "percent_full": 60
//        //            }
//        //        }
//    };

    




class StreamingClient: public BaseClient
{
public:
//    enum class StreamType
//    {
//        FILTER,
//        SAMPLE,
//        FIREHOSE,
//    };
//
//    StreamingClient();
//
//    virtual ~StreamingClient();
//
//    Poco::UUID sample();
//
//    Poco::UUID filter(std::vector<std::string> follow,
//                      std::vector<std::string> track,
//                      std::vector<Geo::CoordinateBounds> locations);
//
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


};


} } // namespace ofx::Twitter
