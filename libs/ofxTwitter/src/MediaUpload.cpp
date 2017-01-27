//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/Twitter/MediaUpload.h"
#include "ofLog.h"
#include <sstream>
#include "Poco/Net/HTTPRequest.h"
#include "ofx/IO/ByteBuffer.h"
#include "ofx/IO/Base64Encoding.h"
#include "ofx/Twitter/Utils.h"


namespace ofx {
namespace Twitter {


const std::string MediaUploadRequest::RESOURCE_URL = "https://upload.twitter.com/1.1/media/upload.json";


MediaUploadRequest::MediaUploadRequest():
    HTTP::PostRequest(RESOURCE_URL, HTTP_1_1)
{
}


MediaUploadRequest::~MediaUploadRequest()
{
}


void MediaUploadRequest::setFile(const std::string& path)
{
    HTTP::PostRequest::addFormFile("media", path, DEFAULT_MEDIA_TYPE);
}


void MediaUploadRequest::setImage(const ofPixels& pixels,
                                  ofImageFormat format,
                                  ofImageQualityType quality)
{
    ofBuffer buffer;
#if OF_VERSION_MINOR < 10
    ofPixels _pixels = pixels;
    ofSaveImage(_pixels, buffer, format, quality);
#else
    ofSaveImage(pixels, buffer, format, quality);
#endif
    HTTP::PostRequest::addFormField("media_data",
                                    IO::Base64Encoding::encode(IO::ByteBuffer(buffer)));
}


MediaUploadResponse::~MediaUploadResponse()
{
}


int64_t MediaUploadResponse::mediaId() const
{
    return _mediaId;
}


void MediaUploadResponse::parseJSON(const ofJson& json)
{
    auto iter = json.cbegin();
    while (iter != json.cend())
    {
        const auto& key = iter.key();
        const auto& value = iter.value();

        if (Utils::endsWith(key, "_str")) { /* skip */ }
        else if (Utils::endsWith(key, "_string")) { /* skip */ }
        else if (key == "media_id") _mediaId = value;
        else if (key == "image") { /* TODO */ }
        else if (key == "size") { /* TODO */ }
        else if (key == "expires_after_secs") { /* TODO */ }
        else ofLogWarning("SearchResponse::parseJSON") << "Unknown key: " << key;

        ++iter;
    }
}


} } // namespace ofx::Twitter
