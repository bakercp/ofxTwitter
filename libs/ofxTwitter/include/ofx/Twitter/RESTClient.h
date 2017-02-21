//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include "ofx/HTTP/OAuth10HTTPClient.h"
#include "ofx/Twitter/Search.h"


namespace ofx {
namespace Twitter {


class SearchResponse;
class MediaUploadResponse;
class StatusUpdateResponse;


/// \brief A RESTClient for the Twitter API.
/// \sa
class RESTClient: public HTTP::OAuth10HTTPClient
{
public:
    /// \brief Create a default RESTClient.
    ///
    /// The user must set the appropriate credentials using the setCredentials()
    /// method before the client will connnect to the Twitter API.
    RESTClient();

    /// \brief Create a RESTClient with the given Credentials.
    /// \param credentials The Twitter Credentials.
    RESTClient(const HTTP::OAuth10Credentials& credentials);

    /// \brief Destroys the REST client.
    virtual ~RESTClient();

    /// \brief Execute a basic Twitter Search query.
    /// \param query The search string to send.
    /// \returns The SearchResponse.
    SearchResponse search(const std::string& query);

    /// \brief Execute a basic Twitter Search query.
    /// \param query The search query to send.
    /// \returns The SearchResponse.
    SearchResponse search(const SearchQuery& query);


//    SearchResponse RESTClient::search(const SearchQuery& query)
//    {
//        
//        
//        
//    }



//    /// \brief Execute a basic Twitter Search query.
//    /// \param query The query string to send.
//    /// \returns The SearchResponse.
//    std::unique_ptr<SearchResponse> search(const std::string& query);

//    /// \brief Execute a Media Upload Request with a path to a file.
//    ///
//    /// This method does not post a status update but completes a media upload.
//    /// The MediaUploadResponse contains the media id that can be referenced in
//    /// a subsequent updateStatus() request.
//    ///
//    /// \param path The path the media that should be uploaded.
//    /// \returns a unique pointer to a MediaUploadResponse.
//    std::unique_ptr<MediaUploadResponse> uploadMedia(const std::string& path);
//
//
//    /// \brief Execute a Media Upload Request with uncompressed pixels.
//    ///
//    /// The uncompressed pixels will be compressed and base64-encoded according
//    /// to the \p format and \p quality parameters.
//    ///
//    /// This method does not post a status update but completes a media upload.
//    /// The MediaUploadResponse contains the media id that can be referenced in
//    /// a subsequent updateStatus() request.
//    ///
//    /// \param pixels The image pixels to send.
//    /// \param format The image format to encode.
//    /// \param quality The compression quality.
//    /// \returns a unique pointer to a MediaUploadResponse.
//    std::unique_ptr<MediaUploadResponse> uploadMedia(const ofPixels& pixels,
//                                                     ofImageFormat format = OF_IMAGE_FORMAT_JPEG,
//                                                     ofImageQualityType quality = OF_IMAGE_QUALITY_MEDIUM);
//
//    /// \brief Update a Twitter Status.
//    ///
//    /// This is a simple status update with no additional parameters set.
//    ///
//    /// \param status The status update to send.
//    /// \returns a unique pointer to a StatusUpdateResponse.
//    std::unique_ptr<StatusUpdateResponse> updateStatus(const std::string& status);
//
//
//    /// \brief Update a Twitter Status and include a image or other media.
//    ///
//    /// This combines MediaUploadRequest and a StatusUpdateRequest allowing the
//    /// user to upload a file and set a Twitter status with one function. This
//    /// method does not require and additional call to uploadMedia.
//    ///
//    /// \param status The status update to send.
//    /// \param path The path the media that should be uploaded.
//    /// \returns a unique pointer to a StatusUpdateResponse.
//    std::unique_ptr<StatusUpdateResponse> updateStatus(const std::string& status,
//                                                       const std::string& path);
//
//    /// \brief Update a Twitter Status and include a image or other media.
//    ///
//    /// This combines MediaUploadRequest and a StatusUpdateRequest allowing the
//    /// user to compress and encode raw pixels and upload and reference them
//    /// and set Twitter status with one function. This method does not require
//    /// and additional call to uploadMedia.
//    ///
//    /// \param status The status update to send.
//    /// \param pixels The image pixels to send.
//    /// \param format The image format to encode.
//    /// \param quality The compression quality.
//    /// \returns a unique pointer to a StatusUpdateResponse.
//    std::unique_ptr<StatusUpdateResponse> updateStatus(const std::string& status,
//                                                       const ofPixels& pixels,
//                                                       ofImageFormat format = OF_IMAGE_FORMAT_JPEG,
//                                                       ofImageQualityType quality = OF_IMAGE_QUALITY_MEDIUM);

};


} } // namespace ofx::Twitter
