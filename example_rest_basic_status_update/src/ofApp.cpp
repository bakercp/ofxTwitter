//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofApp.h"


void ofApp::setup()
{
    ofSetFrameRate(30);

    // First we load credentials from a file. These can also be loaded manually
    // using the ofxTwitter::Credentials constructor.
    //
    // Developers must get their credentials after creating an app at
    // https://apps.twitter.com.
    auto credentials = ofxHTTP::OAuth10Credentials::fromFile("credentials.json");

    // Next we add our credentials to our ofxTwitter::RESTClient.
    client.setCredentials(credentials);

    // Update the Status and add attach an image.
    auto response = client.updateStatus("Hello from openFrameworks!",
                                        "openFrameworks.png");

    // Check the response.
    if (response->isSuccess())
    {
        ofLogNotice("ofApp::setup") << "Success.";
    }
    else
    {
        // List any Twitter errors if they exist.
        for (auto& error: response->errors())
        {
            ofLogError("ofApp::setup") << error.code() << " : " << error.message();
        }
    }
}


void ofApp::draw()
{
    ofBackgroundGradient(ofColor::white, ofColor::black);
    ofDrawBitmapStringHighlight("See console for output.", 30, 30);
}
