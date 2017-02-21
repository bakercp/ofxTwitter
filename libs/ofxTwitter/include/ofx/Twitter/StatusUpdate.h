//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include <string>
#include "ofx/HTTP/PostRequest.h"
#include "ofx/Twitter/BaseResponse.h"
#include "ofx/Twitter/Error.h"
#include "ofx/Twitter/Status.h"


namespace ofx {
namespace Twitter {


/// \brief Updates the user's current status, also known as Tweeting.
///
/// For each update attempt, the update text is compared with the authenticating
/// user's recent Tweets. Any attempt that would result in duplication will be
/// blocked, resulting in a 403 error. Therefore, a user cannot submit the same
/// status twice in a row.
///
/// While not rate limited by the API a user is limited in the number of Tweets
/// they can create at a time. If the number of updates posted by the user
/// reaches the current allowed limit this method will return an HTTP 403 error.
///
/// \sa https://dev.twitter.com/rest/reference/post/statuses/update
class StatusUpdateRequest: public HTTP::PostRequest
{
public:
    /// \brief Create an empty update request.
    StatusUpdateRequest();

    /// \brief Create an update request with the given \p status.
    /// \param status The status to set.
    StatusUpdateRequest(const std::string& status);

    /// \brief Destroy the StatusUpdateRequest.
    virtual ~StatusUpdateRequest();

    /// \brief Set the status.
    ///
    /// The text of your status update, typically up to 140 characters. URL
    /// encode as necessary. t.co link wrapping may affect character counts.
    ///
    /// There are some special commands in this field to be aware of.
    /// For instance, preceding a message with "D " or "M " and following
    /// it with a screen name can create a direct message to that user if the
    /// relationship allows for it.
    ///
    /// \param status The status to set.
    void setStatus(const std::string& status);

    /// \brief The ID of an existing status that the update is in reply to.
    ///
    /// \note This parameter will be ignored unless the author of the tweet this
    /// parameter references is mentioned within the status text. Therefore, you
    /// must include @username, where username is the author of the referenced
    /// tweet, within the update.
    ///
    /// \sa https://support.twitter.com/articles/20069937
    /// \param statusId The status id to reference.
    void setInReplyToStatusId(int64_t statusId);

    /// \brief
    ///
    /// If you upload Tweet media that might be considered sensitive content
    /// such as nudity, violence, or medical procedures, you should set this
    /// value to true. See Media setting and best practices for more context.
    /// Defaults to false.
    void setPossiblySensitive(bool sensitive);

    /// \brief Set the location for this Tweet.
    ///
    /// The latitude of the location this tweet refers to. This parameter will
    /// be ignored unless it is inside the range -90.0 to +90.0 (North is
    /// positive) inclusive. It will also be ignored if there isn't a
    /// corresponding long parameter.
    ///
    /// The longitude of the location this tweet refers to. The valid ranges for
    /// longitude is -180.0 to +180.0 (East is positive) inclusive. This
    /// parameter will be ignored if outside that range, if it is not a number,
    /// if geo_enabled is disabled, or if there not a corresponding lat
    /// parameter.
    ///
    /// \param latitude The latitude of the location this tweet refers to.
    /// \param longitude The longitude of the location this tweet refers to.
    void setCoordinates(double latitude, double longitude);

    /// \brief Set the Place id fro this tweet.
    /// \sa https://dev.twitter.com/overview/api/places
    /// \param placeId The Place id to set.
    void setPlaceId(const std::string& placeId);

    /// \brief Set whether or not to put a pin on the exact coordinates a Tweet.
    /// \param displayCoordinates True if the coordinates should be displayed.
    void setDisplayCoordinates(bool displayCoordinates);

    /// \brief Return less user data.
    ///
    /// When set to true, each Tweet returned in a timeline will include a user
    /// object including only the status authors numerical ID. Omit this
    /// parameter to receive the complete user object.
    ///
    /// \param trimUser True if the user data should be trimmed.
    void setTrimUser(bool trimUser);

    /// \brief Set the media ids to reference.
    ///
    /// A list of media_ids to associate with the Tweet. You may include up to
    /// 4 photos or 1 animated GIF or 1 video in a Tweet.
    ///
    /// \sa MediaUploadRequest
    /// \sa https://dev.twitter.com/rest/media/uploading-media
    /// \param ids A list of the media ids to include.
    void setMediaIds(std::vector<int64_t> ids);

    /// \brief Set the media ids to reference.
    /// \sa setMediaIds()
    /// \param id The media id to reference.
    void setMediaId(int64_t id);

    /// \brief The endpoint URL.
    static const std::string RESOURCE_URL;
};


class StatusUpdateResponse//: public BaseResponse<StatusUpdateRequest>
{
public:
//    using BaseResponse<StatusUpdateRequest>::BaseResponse;

    virtual ~StatusUpdateResponse();

    /// \returns the posted status if successful.
    Status status() const;

protected:
    virtual void parseJSON(const ofJson& json);// override;

private:
    Status _status;

};




} } // namespace ofx::Twitter
