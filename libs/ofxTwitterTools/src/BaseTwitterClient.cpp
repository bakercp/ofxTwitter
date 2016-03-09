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


#include "ofx/Twitter/BaseTwitterClient.h"
#include "ofx/Twitter/Deserializer.h"
#include "ofx/HTTP/PostRequest.h"
#include "ofx/HTTP/GetRequest.h"
#include "ofx/HTTP/OAuth10Credentials.h"


namespace ofx {
namespace Twitter {


BaseTwitterClient::BaseTwitterClient(): BaseTwitterClient(Credentials())
{
}


BaseTwitterClient::BaseTwitterClient(const Credentials& credentials)
{
    setCredentials(credentials);
    addRequestFilter(&_oAuth10RequestFilter);
}


BaseTwitterClient::~BaseTwitterClient()
{
}


void BaseTwitterClient::setCredentials(const Credentials& credentials)
{
    _credentials = credentials;
    _oAuth10RequestFilter.credentials().setConsumerKey(credentials.getConsumerKey());
    _oAuth10RequestFilter.credentials().setConsumerSecret(credentials.getConsumerSecret());
    _oAuth10RequestFilter.credentials().setToken(credentials.getAccessToken());
    _oAuth10RequestFilter.credentials().setTokenSecret(credentials.getAccessTokenSecret());
}


const Credentials& BaseTwitterClient::getCredentials() const
{
    return _credentials;
}


} } // namespace ofx::Twitter
