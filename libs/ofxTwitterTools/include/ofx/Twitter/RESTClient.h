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


#include <stdint.h>
#include "ofx/HTTP/AbstractClientTypes.h"
#include "ofx/HTTP/BaseClient.h"
#include "ofx/HTTP/Context.h"
#include "ofx/HTTP/CredentialStore.h"
#include "ofx/HTTP/DefaultClientHeaders.h"
#include "ofx/HTTP/DefaultProxyProcessor.h"
#include "ofx/HTTP/DefaultRedirectProcessor.h"
#include "ofx/HTTP/DefaultResponseStreamFilter.h"
#include "ofx/HTTP/DefaultSessionProvider.h"
#include "ofx/Twitter/Credentials.h"
#include "ofx/Twitter/SearchQuery.h"
#include "ofx/Twitter/SearchResult.h"


namespace ofx {
namespace Twitter {


class RESTClient: public HTTP::BaseClient
{
public:
    RESTClient();
    
    RESTClient(const Credentials& credentials);

    virtual ~RESTClient();

    void setCredentials(const Credentials& credentials);

    const Credentials& getCredentials() const;


    // throws exceptions
    SearchResult search(const SearchQuery& query);

    // throws exceptions
    void execute(HTTP::BaseRequest& request,
                 HTTP::BaseResponse& response,
                 Json::Value& results);

private:
    void _init();

    Credentials _credentials;

    HTTP::Context _context;

    HTTP::DefaultSessionProvider _defaultSessionProvider;
    HTTP::DefaultClientHeaders _defaultClientHeaders;
    HTTP::DefaultProxyProcessor _defaultProxyProcessor;
    HTTP::DefaultRedirectProcessor _defaultRedirectProcessor;
    HTTP::DefaultResponseStreamFilter _responseStreamFilter;

};


} } // namespace ofx::Twitter
