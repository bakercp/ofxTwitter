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


#include "ofx/Twitter/StatusUpdate.h"
#include "ofLog.h"
#include <sstream>
#include "Poco/Net/HTTPRequest.h"
#include "ofx/HTTP/HTTPUtils.h"


namespace ofx {
namespace Twitter {


const std::string StatusUpdateRequest::RESOURCE_URL = "https://api.twitter.com/1.1/statuses/update.json";


StatusUpdateRequest::StatusUpdateRequest():
    HTTP::PostRequest(RESOURCE_URL, HTTP_1_1)
{
}


StatusUpdateRequest::StatusUpdateRequest(const std::string& status):
    HTTP::PostRequest(RESOURCE_URL, HTTP_1_1)
{
    setStatus(status);
}


StatusUpdateRequest::~StatusUpdateRequest()
{
}


void StatusUpdateRequest::setStatus(const std::string& status)
{
    setFormField("status", status);
}


void StatusUpdateRequest::setInReplyToStatusId(int64_t statusId)
{
    setFormField("in_reply_to_status_id", std::to_string(statusId));
}


void StatusUpdateRequest::setPossiblySensitive(bool sensitive)
{
    setFormField("possibly_sensitive", sensitive ? "true" : "false");
}


void StatusUpdateRequest::setCoordinates(double latitude, double longitude)
{
    setFormField("lat", std::to_string(latitude));
    setFormField("long", std::to_string(longitude));
}


void StatusUpdateRequest::setPlaceId(const std::string& placeId)
{
    setFormField("place_id", placeId);
}


void StatusUpdateRequest::setDisplayCoordinates(bool displayCoordinates)
{
    setFormField("display_coordinates", displayCoordinates ? "true" : "false");
}


void StatusUpdateRequest::setTrimUser(bool trimUser)
{
    setFormField("trim_user", trimUser ? "true" : "false");
}


void StatusUpdateRequest::setMediaIds(std::vector<int64_t> ids)
{
    setFormField("media_ids", HTTP::HTTPUtils::join(ids, " "));
}


void StatusUpdateRequest::setMediaId(int64_t id)
{
    setMediaIds({ id });
}


StatusUpdateResponse::~StatusUpdateResponse()
{
}


Status StatusUpdateResponse::status() const
{
    return _status;
}


void StatusUpdateResponse::parseJSON(const ofJson& json)
{
    _status = Status::fromJSON(json);
}


} } // namespace ofx::Twitter
