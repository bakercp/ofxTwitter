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
