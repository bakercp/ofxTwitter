// =============================================================================
//
// Copyright (c) 2013-2016 Christopher Baker <http://christopherbaker.net>
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
    ofSetFrameRate(30);
    
    // First we load credentials from a file. These can also be loaded manually
    // using the ofxTwitter::Credentials constructor.
    //
    // Developers must get their credentials after creating an app at https://apps.twitter.com
    ofxTwitter::Credentials credentials = ofxTwitter::Credentials::fromFile("credentials.json");

    // Next we add our credentials to our ofxTwitter::RESTClient.
    client.setCredentials(credentials);

    // Finally, we submit our search query and get the result. This can be run
    // in a thread to avoid blocking the program flow.
    //
    // Search results contain information, like the maximum Tweet id that can
    // be used to create the next search query.
    auto result = client.search("love AND hate");

    if (result->isSuccess())
    {
        // We can cycle through the tweets to output their data.
        for (auto& status: result->statuses())
        {
            // Sometimes the user information is not included.
            if (status.user() != nullptr)
            {
                std::cout << ">>" << status.user()->name() << "<< (" << status.user()->screenName() << ")" << std::endl;
            }

            std::cout << status.text() << std::endl << std::endl;
        }

        // We can look through the errors to see if there are any.
        std::cout << "-------------" << std::endl;
        std::cout << "query: " << result->metadata().query() << std::endl;
        std::cout << "count: " << result->metadata().count() << std::endl;
        std::cout << "completed_in: " << result->metadata().completedIn() << std::endl;
        std::cout << "maxId: " << result->metadata().maxId() << std::endl;
        std::cout << "sinceId: " << result->metadata().sinceId() << std::endl;

    }
    else
    {
        for (auto& error: result->errors())
        {
            std::cout << error.code() << " / " << error.message() << std::endl;
        }

        std::cout << result->error() << std::endl;
    }
}


void ofApp::draw()
{
    ofBackgroundGradient(ofColor::white, ofColor::black);
    ofDrawBitmapStringHighlight("See console for output.", 30, 30);
}
