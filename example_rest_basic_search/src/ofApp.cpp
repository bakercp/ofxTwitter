//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofApp.h"


void ofApp::setup()
{
//    ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetFrameRate(30);

    client.registerSearchEvents(this);

    // First we load credentials from a file. These can also be loaded manually
    // using the ofxTwitter::Credentials constructor.
    //
    // Developers must get their credentials after creating an app at https://apps.twitter.com
    client.setCredentialsFromFile("NetworkedObject.json");

    // Set the polling interval for 6 seconds.
    client.setPollingInterval(600000);

    // This starts the search.
    client.search("#selfieseer");


    
}


void ofApp::draw()
{
    ofBackground(0);

    auto total = count + countMissed;

    std::stringstream ss;
    ss << "  Received: " << count << std::endl;
    ss << "    Missed: " << countMissed << std::endl;
    ss << "     Total: " << total << std::endl;

    std::string received = "...";

    if (total > 0)
    {
        received = ofToString(static_cast<double>(count) / total * 100, 2);
    }

    ss << "% Received: " << received;

    ofDrawBitmapStringHighlight(ss.str(), 14, 20);
}


bool ofApp::onStatus(const void* source, const ofxTwitter::Status& status)
{
    count++;
    ofLogNotice("ofApp::onStatus") << "Text: " << status.text();
    ofLogNotice("ofApp::onStatus") << "Coordinates: " << (status.coordinates() ? ofToString(status.coordinates()) : "NONE");
    ofLogNotice("ofApp::onStatus") << "Place: " << (status.place() ? ofToString(status.place()->fullName()) : "NONE");
    return true;
}


bool ofApp::onError(const void* source, const ofxTwitter::Error& error)
{
    ofLogError("ofApp::onError") << "Error: " << error.code() << " " << error.message();
    return true;
}


bool ofApp::onException(const void* source, const std::exception& notice)
{
    ofLogError("ofApp::onException") << "Exception: " << notice.what();
    return true;
}


bool ofApp::onMessage(const void* source, const ofJson& json)
{
    return true;
}
