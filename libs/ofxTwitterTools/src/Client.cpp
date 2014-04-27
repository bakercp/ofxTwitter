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


#include "ofx/Twitter/Client.h"


namespace ofx {
namespace Twitter {


Client::Client():
    _lastID(0),
    _query("")
{
}


Client::~Client()
{
}


void Client::setup(const std::string& consumerKey,
                   const std::string& consumerSecret,
                   const std::string& query,
                   int64_t lastID)
{
    _query = query;
    _lastID = lastID;

    ofxOAuth::setup("https://api.twitter.com",
                    consumerKey,
                    consumerSecret);

}


bool Client::search()
{
    std::stringstream ss;

    ss << "/1.1/search/tweets.json?";
    ss << "since_id=" << _lastID;
    ss << "&q=" << _query;
    ss << "&include_entities=true";
    ss << "&result_type=recent";
    ss << "&count=100";

    std::string result = get(ss.str());

//    ofBuffer buffer = ofBufferFromFile("grrr_statuses.json");
//    std::string result = buffer.getText();

    if (!result.empty())
    {
        std::vector<Tweet> tweets;

        if (Deserializer::deserialize(result, tweets))
        {
            ofScopedLock lock(_mutex);
            _tweets.insert(_tweets.end(), tweets.begin(), tweets.end());

            std::vector<Tweet>::const_iterator iter = _tweets.begin();

            while (iter != _tweets.end())
            {
                const Tweet& tweet = (*iter);

                int64_t ID = tweet.getID();
                 _lastID = std::max(ID, _lastID);


                if(!tweet.getUser().isNull())
                {
                    const User& user = tweet.getUser().value();

                    cout << "User: " << user.getScreenName() << " : " << user.getName() << endl;

                }
                else
                {
                    cout << "NO USER SPECIFIED" << endl;
                }

                cout << "\t" << tweet.getID() << " " << tweet.getText() << endl;

                ++iter;
            }

            cout << "LAST ID = " << _lastID << endl;

            return true;
        }
        else
        {
            ofLogError("TwitterClient::search()") << "Unable to deserialize response from " << _query;;
            return false;
        }
    }
    else
    {
        ofLogError("TwitterClient::search()") << "Search " << _query << " returned nothing.";
        return false;
    }
}

    
} } // namespace ofx::Twitter
