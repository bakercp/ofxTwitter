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
class MediaUploadResponse: public BaseResponse<MediaUploadRequest>
{
public:
    using BaseResponse<MediaUploadRequest>::BaseResponse;

    virtual ~MediaUploadResponse();

    int64_t mediaId() const;

protected:
    virtual void parseJSON(const ofJson& json) override;

private:
    int64_t _mediaId;

};



} } // namespace ofx::Twitter
