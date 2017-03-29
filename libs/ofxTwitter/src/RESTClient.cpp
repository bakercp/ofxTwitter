//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/Twitter/RESTClient.h"
#include "ofx/HTTP/GetRequest.h"
#include "ofx/Twitter/MediaUpload.h"
#include "ofx/Twitter/Search.h"
#include "ofx/Twitter/StatusUpdate.h"


namespace ofx {
namespace Twitter {


//RESTClient::RESTClient()
//{
//}
//
//
//RESTClient::RESTClient(const HTTP::OAuth10Credentials& credentials):
//    HTTP::OAuth10HTTPClient(credentials)
//{
//}
//
//
//RESTClient::~RESTClient()
//{
//}
//
//SearchResponse RESTClient::search(const std::string& query)
//{
//    return search(SearchQuery(query));
//}
//
//
//SearchResponse RESTClient::search(const SearchQuery& query)
//{
//    HTTP::GetRequest request(SearchQuery::RESOURCE_URL);
//    request.addFormFields(query);
//    return SearchResponse::fromHTTPResponse(*execute(request));
//}
//



//std::unique_ptr<SearchResponse> RESTClient::search(const std::string& query)
//{
//    auto request = std::make_unique<SearchRequest>(query);
//
//    return executeBuffered<SearchRequest, SearchResponse>(std::move(request));
//}
//
//
//std::unique_ptr<MediaUploadResponse> RESTClient::uploadMedia(const std::string& path)
//{
//    auto request = std::make_unique<MediaUploadRequest>();
//    request->setFile(path);
//    return executeBuffered<MediaUploadRequest, MediaUploadResponse>(std::move(request));
//}
//
//
//std::unique_ptr<MediaUploadResponse> RESTClient::uploadMedia(const ofPixels& pixels,
//                                                             ofImageFormat format,
//                                                             ofImageQualityType quality)
//{
//    auto request = std::make_unique<MediaUploadRequest>();
//    request->setImage(pixels, format, quality);
//    return executeBuffered<MediaUploadRequest, MediaUploadResponse>(std::move(request));
//}
//
//
//std::unique_ptr<StatusUpdateResponse> RESTClient::updateStatus(const std::string& status)
//{
//    auto updateRequest = std::make_unique<StatusUpdateRequest>(status);
//    return executeBuffered<StatusUpdateRequest, StatusUpdateResponse>(std::move(updateRequest));
//}
//
//
//std::unique_ptr<StatusUpdateResponse> RESTClient::updateStatus(const std::string& status,
//                                                               const std::string& path)
//{
//    auto response = uploadMedia(path);
//
//    auto updateRequest = std::make_unique<StatusUpdateRequest>(status);
//
//    if (response->isSuccess())
//    {
//        ofLogVerbose("RESTClient::updateStatus") << "Media id " << response->mediaId();
//        updateRequest->setMediaId(response->mediaId());
//    }
//    else
//    {
//        ofLogError("RESTClient::updateStatus") << "Unable to upload media: " << path;
//        for (auto& error: response->errors())
//        {
//            ofLogError("RESTClient::updateStatus") << "\t" << error.code() << " : " << error.message();
//        }
//    }
//
//    return executeBuffered<StatusUpdateRequest, StatusUpdateResponse>(std::move(updateRequest));
//}
//
//
//std::unique_ptr<StatusUpdateResponse> RESTClient::updateStatus(const std::string& status,
//                                                               const ofPixels& pixels,
//                                                               ofImageFormat format,
//                                                               ofImageQualityType quality)
//{
//    auto response = uploadMedia(pixels, format, quality);
//
//    auto updateRequest = std::make_unique<StatusUpdateRequest>(status);
//
//    if (response->isSuccess())
//    {
//        updateRequest->setMediaId(response->mediaId());
//    }
//    else
//    {
//        ofLogError("RESTClient::updateStatus") << "Unable to upload pixel media.";
//        for (auto& error: response->errors())
//        {
//            ofLogError("RESTClient::updateStatus") << "\t" << error.code() << " : " << error.message();
//        }
//    }
//
//    return executeBuffered<StatusUpdateRequest, StatusUpdateResponse>(std::move(updateRequest));
//}


} } // namespace ofx::Twitter
