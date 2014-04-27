// =============================================================================
//
// Copyright (c) 2009-2013 Christopher Baker <http://christopherbaker.net>
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
#include "ofxOAuth.h"
#include "ofx/Twitter/Tweet.h"
#include "ofx/Twitter/Deserializer.h"


namespace ofx {
namespace Twitter {


class Client: public ofxOAuth
{
public:
    Client();
    virtual ~Client();

    virtual void setup(const std::string& consumerKey,
                       const std::string& consumerSecret,
                       const std::string& query,
                       int64_t lastId);

    bool search();

    std::string getQuery() const
    {
        ofScopedLock lock(_mutex);
        return _query;
    }

    uint64_t getLastId() const
    {
        ofScopedLock lock(_mutex);
        return _lastID;
    }

    Tweet nextTweet()
    {
        ofScopedLock lock(_mutex);
        Tweet tweet;

        if(!_tweets.empty())
        {
            tweet = _tweets.front();
            _tweets.erase(_tweets.begin());
        }
        return tweet;
    }

    std::size_t size() const
    {
        ofScopedLock lock(_mutex);
        return _tweets.size();
    }

private:
    std::string _query;
    int64_t _lastID;

    std::vector<Tweet> _tweets;

    mutable ofMutex _mutex;

};


} } // namespace ofx::Twitter
