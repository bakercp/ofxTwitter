// =============================================================================
//
// Copyright (c) 2009-2015 Christopher Baker <http://christopherbaker.net>
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


#include "ofx/Twitter/BaseTwitterClient.h"
#include "ofx/Twitter/SearchQuery.h"
#include "ofx/Twitter/SearchResult.h"


namespace ofx {
namespace Twitter {


/// \brief A RESTClient for the Twitter API.
/// \sa
class RESTClient: public BaseTwitterClient
{
public:
    /// \brief Create a default RESTClient.
    ///
    /// The user must set the appropriate credentials using the setCredentials()
    /// method before the client will connnect to the Twitter API.
    RESTClient();

    /// \brief Create a RESTClient with the given Credentials.
    /// \param credentials The Twitter Credentials.
    RESTClient(const Credentials& credentials);

    /// \brief Destroys the REST client.
    virtual ~RESTClient();

    /// \brief Execute a Twitter Search query.
    /// \param query The query parameters to send.
    /// \throws Various HTTP exceptions and Poco::SyntaxException.
    /// \returns The SearchResult, including errors if any.
    SearchResult search(const SearchQuery& query);

    /// \brief Execute an arbitrary OAuth 1.0 authenticated HTTP request.
    /// \param request The HTTP Request to send.
    /// \param response The HTTP Response to receive.
    /// \param results The JSON (if any to parse) from the executed response.
    /// \throws Various HTTP exceptions and Poco::SyntaxException.
    void execute(HTTP::BaseRequest& request,
                 HTTP::BaseResponse& response,
                 Json::Value& results);

};


} } // namespace ofx::Twitter
