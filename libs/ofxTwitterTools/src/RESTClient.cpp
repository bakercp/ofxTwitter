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


#include "ofx/Twitter/RESTClient.h"
#include "ofx/HTTP/GetRequest.h"
#include "ofx/Twitter/MediaUpload.h"
#include "ofx/Twitter/Search.h"
#include "ofx/Twitter/StatusUpdate.h"


namespace ofx {
namespace Twitter {


RESTClient::RESTClient()
{
}


RESTClient::RESTClient(const HTTP::OAuth10Credentials& credentials):
    HTTP::OAuth10HTTPClient(credentials)
{
}


RESTClient::~RESTClient()
{
}


std::unique_ptr<SearchResponse> RESTClient::search(const std::string& query)
{
    auto request = std::make_unique<SearchRequest>(query);

    return executeBuffered<SearchRequest, SearchResponse>(std::move(request));
}


std::unique_ptr<MediaUploadResponse> RESTClient::uploadMedia(const std::string& path)
{
    auto request = std::make_unique<MediaUploadRequest>();
    request->setFile(path);
    return executeBuffered<MediaUploadRequest, MediaUploadResponse>(std::move(request));
}


std::unique_ptr<MediaUploadResponse> RESTClient::uploadMedia(const ofPixels& pixels,
                                                             ofImageFormat format,
                                                             ofImageQualityType quality)
{
    auto request = std::make_unique<MediaUploadRequest>();
    request->setImage(pixels, format, quality);
    return executeBuffered<MediaUploadRequest, MediaUploadResponse>(std::move(request));
}


std::unique_ptr<StatusUpdateResponse> RESTClient::updateStatus(const std::string& status)
{
    auto updateRequest = std::make_unique<StatusUpdateRequest>(status);
    return executeBuffered<StatusUpdateRequest, StatusUpdateResponse>(std::move(updateRequest));
}


std::unique_ptr<StatusUpdateResponse> RESTClient::updateStatus(const std::string& status,
                                                               const std::string& path)
{
    auto response = uploadMedia(path);

    auto updateRequest = std::make_unique<StatusUpdateRequest>(status);

    if (response->isSuccess())
    {
        ofLogVerbose("RESTClient::updateStatus") << "Media id " << response->mediaId();
        updateRequest->setMediaId(response->mediaId());
    }
    else
    {
        ofLogError("RESTClient::updateStatus") << "Unable to upload media: " << path;
        for (auto& error: response->errors())
        {
            ofLogError("RESTClient::updateStatus") << "\t" << error.code() << " : " << error.message();
        }
    }

    return executeBuffered<StatusUpdateRequest, StatusUpdateResponse>(std::move(updateRequest));
}


std::unique_ptr<StatusUpdateResponse> RESTClient::updateStatus(const std::string& status,
                                                               const ofPixels& pixels,
                                                               ofImageFormat format,
                                                               ofImageQualityType quality)
{
    auto response = uploadMedia(pixels, format, quality);

    auto updateRequest = std::make_unique<StatusUpdateRequest>(status);

    if (response->isSuccess())
    {
        updateRequest->setMediaId(response->mediaId());
    }
    else
    {
        ofLogError("RESTClient::updateStatus") << "Unable to upload pixel media.";
        for (auto& error: response->errors())
        {
            ofLogError("RESTClient::updateStatus") << "\t" << error.code() << " : " << error.message();
        }
    }

    return executeBuffered<StatusUpdateRequest, StatusUpdateResponse>(std::move(updateRequest));
}


} } // namespace ofx::Twitter
