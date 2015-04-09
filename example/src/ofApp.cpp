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


#include "ofApp.h"


void ofApp::setup()
{

    client.setup("T5Ll4TNkiBtnJSeXOJWL2SB5B",
                 "QqZYNZDJ45yg41gCw7hpXdRapI6EOlXbkMqZTXPmYKWyfIH2Vq",
                 "love",
                 0);

    client.search();
}


void ofApp::update()
{
}


void ofApp::draw()
{
    ofBackground(0);

    std::stringstream ss;

    ss << ofx::Time::Utils::format(tweet.getCreatedAt()) << std::endl;

    if (!tweet.getUser().isNull())
    {
        const ofx::Twitter::User& user = tweet.getUser().value();
        ss << user.getName() << std::endl;
        ss << ofx::Time::Utils::format(tweet.getCreatedAt()) << std::endl;
    }

    ss << tweet.getText() << std::endl;

    ofDrawBitmapString(ss.str(), ofVec2f(14, 14));
}


void ofApp::keyPressed(int key)
{
    tweet = client.nextTweet();
}
