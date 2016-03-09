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
    ofx::Twitter::Credentials credentials = ofx::Twitter::Credentials::fromFile("NetworkedObject.json");

    client.setCredentials(credentials);

    ofx::Twitter::SearchQuery query("love AND hate");
    query.setCount(1);

//    query.setMaxId(585870359045349376);

//    Twitter::UpdateRequest request("Image upload!");
//    request.addFormField("media_ids", "585667540694753281,585668476301377537");

//    585668476301377537
//    Twitter::UploadRequest request;
//
//    request.addFormFile("Puppy_2.jpg");

    ofx::Twitter::SearchResult result = client.search(query);

    std::cout << result.errors().size() << std::endl;

    for (const ofx::Twitter::Error& error : result.errors())
    {
        std::cout << error.code() << " / " << error.message() << std::endl;
    }

    for (const ofx::Twitter::Tweet& tweet : result.tweets())
    {
        if (!tweet.user().isNull())
        {
            const ofx::Twitter::User& user = tweet.user();

            std::cout << ">>" << user.getName() << "<< (" << user.getScreenName() << ")" << std::endl;
        }

        std::cout << tweet.text() << std::endl << std::endl;
    }

    std::cout << "-------------" << std::endl;
    std::cout << "completed_in: " << result.completedIn() << std::endl;
    std::cout << "count: " << result.count() << std::endl;
    std::cout << "maxId: " << result.maxId() << std::endl;
    std::cout << "sinceId: " << result.sinceId() << std::endl;
    std::cout << "query: " << result.query() << std::endl;

    std::cout << result.status() << std::endl;
    std::cout << result.reasonForStatus() << std::endl;
}


void ofApp::draw()
{
    ofBackgroundGradient(ofColor::white, ofColor::black);
    ofDrawBitmapStringHighlight("See console for output.", ofPoint(30, 30));
}
