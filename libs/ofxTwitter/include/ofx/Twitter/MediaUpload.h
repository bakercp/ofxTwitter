//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include <string>
#include "ofImage.h"
#include "ofx/Twitter/Status.h"
#include "ofx/Twitter/BaseResponse.h"
#include "ofx/Twitter/Error.h"
#include "ofx/HTTP/PostRequest.h"


namespace ofx {
namespace Twitter {


/// \brief A Twitter media upload request.
/// \sa https://dev.twitter.com/rest/reference/post/media/upload
class MediaUploadRequest: public HTTP::PostRequest
{
public:
    /// \brief Create an empty MediaUploadRequest.
    MediaUploadRequest();

    /// \brief Destroy the MediaUploadRequest.
    virtual ~MediaUploadRequest();

    /// \brief The raw binary file content being uploaded.
    /// \param path The path the media that should be uploaded.
    void setFile(const std::string& path);

    /// \brief Set the image from an image file.
    /// \param pixels The image pixels to send.
    /// \param format The image format to encode.
    /// \param quality The compression quality.
    void setImage(const ofPixels& pixels,
                  ofImageFormat format = OF_IMAGE_FORMAT_JPEG,
                  ofImageQualityType quality = OF_IMAGE_QUALITY_MEDIUM);


    /// \brief The default resource URL.
    static const std::string RESOURCE_URL;

};


/// \brief A Twitter MediaUploadResponse.
class MediaUploadResponse//: public BaseResponse<MediaUploadRequest>
{
public:
//    using BaseResponse<MediaUploadRequest>::BaseResponse;

    virtual ~MediaUploadResponse();

    int64_t mediaId() const;

protected:
    virtual void parseJSON(const ofJson& json);// override;

private:
    int64_t _mediaId;

};



} } // namespace ofx::Twitter
