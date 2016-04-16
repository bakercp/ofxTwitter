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

    auto mediaRequest = std::make_unique<ofxTwitter::MediaUploadRequest>();

    mediaRequest->setFile("openFrameworks.png");

    auto response = client.executeBuffered<ofxTwitter::MediaUploadRequest, ofxTwitter::MediaUploadResponse>(std::move(mediaRequest));

    cout << std::to_string(response->mediaId()) << endl;

    auto updateRequest = std::make_unique<ofxTwitter::StatusUpdateRequest>("This is a test of the system!");

    updateRequest->setMediaId(response->mediaId());

    auto updateResponse = client.executeBuffered<ofxTwitter::StatusUpdateRequest, ofxTwitter::StatusUpdateResponse>(std::move(updateRequest));

    cout << updateResponse->getBuffer() << endl;

    //    {"expires_after_secs":86400,"image":{"h":114,"image_type":"image/png","w":114},"media_id":720454264901013504,"media_id_string":"720454264901013505","size":3976}

//    ofxTwitter::UpdateRequest request("Image upload!");
//    request.addFormField("media_ids", "585667540694753281,585668476301377537");

}


void ofApp::draw()
{
    ofBackgroundGradient(ofColor::white, ofColor::black);
    ofDrawBitmapStringHighlight("See console for output.", 30, 30);
}
