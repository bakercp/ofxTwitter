//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include <string>
#include <vector>
#include "Poco/Net/NameValueCollection.h"


namespace ofx {
namespace Twitter {


/// \brief Parameters needed to request Twitter Streams.
/// \sa https://dev.twitter.com/streaming/overview/request-parameters
class StreamingQuery: public Poco::Net::NameValueCollection
{
public:
    /// \brief Possible values for the `delimited` request parameter.
    /// \sa https://dev.twitter.com/streaming/overview/request-parameters#delimited
    enum class Delimited
    {
        DEFAULT,
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

    /// \brief Destroy the StreamingQuery.
    virtual ~StreamingQuery();

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
    /// sample.
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

};


} } // namespace ofx::Twitter
