//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//

#pragma once


#include <string>
#include <map>
#include <vector>
#include "Poco/DateTime.h"
#include "ofx/Geo/Coordinate.h"
#include "ofx/Twitter/Entities.h"
#include "ofx/Twitter/Place.h"


// Undefine Status from Xlib.h.
#ifdef Status
#undef Status
#endif


namespace ofx {
namespace Twitter {


class User;
class BaseNamedUser;


/// \brief The Twitter Status object.
/// \sa https://dev.twitter.com/overview/api/tweets
class Status
{
public:
    /// \brief A typedef for Status Annotations.
    typedef std::map<std::string, std::string> Annotations;

    /// \brief The filter level used for streaming endpoints.
    ///
    /// Setting this parameter to one of none, low, or medium will set the
    /// minimum value of the filter_level Tweet attribute required to be
    /// included in the stream. The default value is none, which includes all
    /// available Tweets.
    ///
    /// When displaying a stream of Tweets to end users (dashboards or live
    /// feeds at a presentation or conference, for example) it is suggested
    /// that you set this value to medium.
    enum class FilterLevel
    {
        /// \brief No filtering.
        NONE,
        /// \brief Low filtering.
        LOW,
        /// \brief Medium filtering.
        MEDIUM
    };

    /// \brief A class representing basic metadata.
    class Metadata
    {
    public:
        /// returns the ISO language code.
        std::string isoLanguageCode() const;

        /// \todo Would be nice to return SearchRequest::RESULT_TYPE.
        std::string resultType() const;

        /// \brief Parse a Metadata from the given JSON.
        /// \param json The JSON to parse.
        /// \returns a parsed Metadata.
        static Metadata fromJSON(const ofJson& json);

    private:
        /// \brief The ISO language code.
        std::string _isoLanguageCode;

        /// \brief The result type.
        std::string _resultType;

    };

    /// \brief Create a default empty Status.
    Status();

    /// \brief Destroy the Status.
    virtual ~Status();

    /// \returns the Twitter URL `https://twitter.com/statuses/{id}`.
    std::string url() const;

    /// \brief The unique identifier for this Status.
    /// \returns the id.
    int64_t id() const;

    /// \returns the user or nullptr if no user is specified.
    const User* user() const;

    /// \returns the display text.
    std::string displayText() const;

    /// \brief Returns the machine detected BCP 47 language code for the Status.
    ///
    /// The machine-detected BCP 47 language identifier corresponding to the
    /// machine-detected language of the Tweet text, or und if no language could
    /// be detected.
    ///
    /// \returns the machine-detected language of the Tweet.
    std::string language() const;

    /// \return the Tweet annotations.
    Annotations annotations() const;

    /// \brief Get a list of the controbutors.
    ///
    /// A collection of brief user objects (usually only one) indicating users
    /// who contributed to the authorship of the tweet, on behalf of the
    /// official tweet author. This is a legacy value and is not actively used.
    ///
    /// \deprecated
    ///
    /// \returns the list of contributors.
    std::vector<BaseNamedUser> contributors() const;

    /// \returns the Tweet coordinates, or nullptr if none.
    const Geo::Coordinate* coordinates() const;

    /// \returns The created-at time.
    Poco::DateTime createdAt() const;

    /// \returns The UTC offset extracted from the time.
    int64_t utcOffset() const;

    /// \brief The id of the retweet if the authorizing user retweeted this tweet.
    ///
    /// Found when on methods supporting the `include_my_retweet` parameter,
    /// when set to true.
    ///
    /// \returns the retweet id.
    int64_t currentUserRetweet() const;

    /// \returns Entities which have been parsed out of the text of the Tweet.
    Entities entities() const;

    /// \returns Entities which have been parsed out of the text of the Tweet.
    Entities extendedEntities() const;

    /// \returns the extended Tweet or nullptr if none.
    const Status* extendedTweet() const;

    /// \returns the approximate number of times this Tweet has been liked, or -1 if unknown;
    int64_t favoriteCount() const;

    /// \returns true if this is a quoted status.
    bool isQuoteStatus() const;

    /// \returns the quoted status id or -1 if none.
    int64_t quotedStatusId() const;

    /// \returns the quoted status, or nullptr if none.
    const Status* quotedStatus() const;

    /// \brief Indicates if this Tweet has been liked by the authenticating user.
    bool favorited() const;

    /// \brief The filter level of this Tweet.
    ///
    /// Indicates the maximum value of the filter_level parameter which may be
    /// used and still stream this Tweet. So a value of medium will be streamed
    /// on none, low, and medium streams.
    ///
    /// \returns the filter status.
    FilterLevel filterLevel() const;

    /// \returns the screen name of the original Tweet’s author, or empty.
    std::string inReplyToScreenName() const;

    /// \returns the status id of the original Tweet's if retweeted, or -1.
    int64_t inReplyToStatusId() const;

    /// \returns the user id of the original Tweet's author if retweeted, or -1.
    int64_t inReplyToUserId() const;

    /// \brief True if any linked content may be sensitive.
    ///
    /// The meaning of the field doesn’t pertain to the Tweet content itself,
    /// but instead it is an indicator that the URL contained in the Tweet may
    /// contain content or media identified as sensitive content.
    ///
    /// \returns whether the linked content may be sensitive.
    bool possiblySensitive() const;

    /// \brief The Scopes of the Tweet.
    ///
    /// A set of key-value pairs indicating the intended contextual delivery of
    /// the containing Tweet. Currently used by Twitter’s Promoted Products.
    ///
    /// \returns the scopes of this Tweet.
    std::map<std::string, bool> scopes() const;

    /// \returns the number of times this Tweet has been retweeted.
    int64_t retweetCount() const;

    /// \returns whether this Tweet has been retweeted by the authenticating user.
    bool retweeted() const;

    /// \brief An optional Tweet.
    ///
    /// We use a std::shared_ptr to keep track to make it nullable and avoid
    /// the hassle of std::unique_ptr and copies.
    ///
    /// \returns the retweeted status or nullptr if not available.
    const Status* retweetedStatus() const;

    /// \brief Utility used to post the Tweet, as an HTML-formatted string.
    ///
    /// Tweets from the Twitter website have a source value of web.
    ///
    /// \returns the Tweet source.
    std::string source() const;

    /// \returns the actual UTF-8 text of the status update.
    std::string text() const;

    /// \returns the full text if this is an extended tweet.
    std::string fullText() const;

    /// \returns the start index of the display text.
    std::string::size_type displayTextStart() const;

    /// \returns the end index of the display text.
    std::string::size_type displayTextEnd() const;

    /// \brief Indicates whether the value of the text parameter was truncated.
    ///
    /// For example, as a result of a retweet exceeding the 140 character Tweet
    /// length. Truncated text will end in ellipsis, like this ... Since Twitter
    /// now rejects long Tweets vs truncating them, the large majority of Tweets
    /// will have this set to false.
    ///
    /// \note while native retweets may have their toplevel text property
    /// shortened, the original text will be available under the
    /// _retweetedStatus object and the truncated parameter will be set to the
    /// value of the original status (in most cases, false ).
    ///
    /// \returns true if truncated.
    bool truncated() const;

    /// \returns whether the Tweet has been withheld due to a DMCA complaint.
    bool withheldCopyright() const;

    /// \brief A set of countries/codes indicating where a Status is witheld.
    ///
    /// When present, indicates a list of uppercase two-letter country codes
    /// this content is withheld from. Twitter supports the following
    /// non-country values for this field:
    /// - "XX" - Content is withheld in all countries
    /// - "XY” - Content is withheld due to a DMCA request
    ///
    /// \returns the withheld in contries.
    std::vector<std::string> withheldInCountries() const;

    /// \returns whether the witheld content is the "status" or a "user".
    std::string withheldScope() const;

    /// \returns the optional Place data.
    const Place* place() const;

    /// \returns the Status metadata.
    Metadata metadata() const;
    
    /// \returns the streaming timestamp in milliseconds.
    uint64_t timestamp() const;

    /// \returns the original json.
    ofJson json() const;

    /// \brief Parse a Status from the given JSON.
    /// \param json The JSON to parse.
    /// \returns a parsed Status.
    static Status fromJSON(const ofJson& json);

protected:
    /// \brief The unique identifier for this Tweet.
    int64_t _id = -1;

    /// \brief Optional user data.
    ///
    /// We use a std::shared_ptr to keep track to make it nullable and avoid
    /// the hassle of std::unique_ptr and copies.
    std::shared_ptr<User> _user = nullptr;

    /// \brief The Annotations.
    Annotations _annotations;

    /// \brief Get a list of the controbutors.
    ///
    /// A collection of brief user objects (usually only one) indicating users
    /// who contributed to the authorship of the tweet, on behalf of the
    /// official tweet author. This is a legacy value and is not actively used.
    std::vector<BaseNamedUser> _contributors;

    /// \brief Optional location data.
    ///
    /// We use a std::shared_ptr to keep track to make it nullable and avoid
    /// the hassle of std::unique_ptr and copies.
    std::shared_ptr<Geo::Coordinate> _coordinates;

    /// \brief The created-at time.
    Poco::DateTime _createdAt;

    /// \brief The UTC offset extracted from the time.
    int64_t _utcOffset = 0;

    /// \brief Perspectival Only.
    ///
    /// Found when on methods supporting the `include_my_retweet` parameter,
    /// when set to true.
    int64_t _currentUserRetweet = -1;

    /// \brief Entities which have been parsed out of the text of the Tweet.
    Entities _entities;

    /// \brief Entities which have been parsed out of the text of the Tweet.
    Entities _extendedEntities;

    /// \brief The extended tweet.
    std::shared_ptr<Status> _extendedTweet = nullptr;

    /// \brief Approximately how many times this Tweet has been liked;
    ///
    /// If unknown, this value will be -1;
    int64_t _favoriteCount = -1;

    /// \brief True if this is a quote Tweet.
    bool _isQuoteStatus = false;

    /// \brief If a quote Tweet, this includes the ID of the quoted Tweet.
    int64_t _quotedStatusId = -1;

    /// \brief If this is a quoted Tweet, this will be non-null.
    std::shared_ptr<Status> _quotedStatus = nullptr;

    /// \brief Indicates if this Tweet has been liked by the authenticating user.
    bool _favorited = false;

    /// \brief The filter level of this Tweet.
    ///
    /// Indicates the maximum value of the filter_level parameter which may be
    /// used and still stream this Tweet. So a value of medium will be streamed
    /// on none, low, and medium streams.
    FilterLevel _filterLevel = FilterLevel::NONE;

    /// \brief If this is a reply, the screen name of the original Tweet’s author.
    std::string _inReplyToScreenName;

    /// \brief If this is a reply, the id of the original Tweet.
    int64_t _inReplyToStatusId = -1;

    /// \brief If this is a reply, the user id of the original Tweet's author.
    int64_t _inReplyToUserId = -1;

    /// \brief BCP 47 language identifier corresponding to the machine-detected
    /// language of the Tweet text, or `und` if no language could be detected
    std::string _language;

    /// \brief True if any linked content may be sensitive.
    ///
    /// The meaning of the field doesn’t pertain to the Tweet content itself,
    /// but instead it is an indicator that the URL contained in the Tweet may
    /// contain content or media identified as sensitive content.
    bool _possiblySensitive = false;

    /// \brief The Scopes of the Tweet.
    ///
    /// A set of key-value pairs indicating the intended contextual delivery of
    /// the containing Tweet. Currently used by Twitter’s Promoted Products.
    std::map<std::string, bool> _scopes;

    /// \brief Number of times this Tweet has been retweeted.
    int64_t _retweetCount = -1;

    /// \brief Indicates whether this Tweet has been retweeted by the authenticating user.
    bool _retweeted = false;

    /// \brief An optional Tweet.
    ///
    /// We use a std::shared_ptr to keep track to make it nullable and avoid
    /// the hassle of std::unique_ptr and copies.
    std::shared_ptr<Status> _retweetedStatus = nullptr;

    /// \brief Utility used to post the Tweet, as an HTML-formatted string.
    ///
    /// Tweets from the Twitter website have a source value of web.
    std::string _source;

    /// \brief The actual UTF-8 text of the status update.
    std::string _text;

    /// \brief The full text if this is an extended tweet.
    std::string _fullText;

    /// \brief The start index of the display text.
    std::string::size_type _displayTextStart = 0;

    /// \brief The end index of the display text.
    std::string::size_type _displayTextEnd = 0;

    /// \brief Indicates whether the value of the text parameter was truncated.
    ///
    /// For example, as a result of a retweet exceeding the 140 character Tweet
    /// length. Truncated text will end in ellipsis, like this ... Since Twitter
    /// now rejects long Tweets vs truncating them, the large majority of Tweets
    /// will have this set to false.
    ///
    /// \note while native retweets may have their toplevel text property
    /// shortened, the original text will be available under the
    /// _retweetedStatus object and the truncated parameter will be set to the
    /// value of the original status (in most cases, false ).
    bool _truncated = false;

    /// \brief Indicates if Tweet has been withheld due to a DMCA complaint.
    bool _withheldCopyright = false;

    /// \brief A set of countries/codes indicating where a Status is witheld.
    ///
    /// When present, indicates a list of uppercase two-letter country codes
    /// this content is withheld from. Twitter supports the following
    /// non-country values for this field:
    /// - "XX" - Content is withheld in all countries
    /// - "XY” - Content is withheld due to a DMCA request
    std::vector<std::string> _withheldInCountries;

    /// \brief Indicates whether withheld content is the "status" or a "user".
    std::string _withheldScope;

    /// \brief Optional Place data.
    std::shared_ptr<Place> _place = nullptr;

    /// \brief The Status metadata.
    Metadata _metadata;

    /// \brief The streaming timestamp in milliseconds.
    uint64_t _timestamp = 0;

    /// \brief The original json.
    ofJson _json;

};


} } // namespace ofx::Twitter
