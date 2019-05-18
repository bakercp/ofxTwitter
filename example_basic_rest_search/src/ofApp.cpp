//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofApp.h"


void ofApp::setup()
{
    ofSetFrameRate(30);

    // Easily register for all search events.
    client.registerSearchEvents(this);

    // First we load credentials from a file. These can also be loaded manually
    // using the ofxTwitter::Credentials constructor.
    //
    // Developers must get their credentials after creating an app at
    // https://apps.twitter.com
    client.setCredentialsFromFile("credentials.json");

    // Set the polling interval for 6 seconds.
    // Results will appear in the callbacks onStatus(..), onError(...), etc.
    // The thread is synchronized with the update() loop by default and is
    // thread-safe.
    client.setPollingInterval(6000);

    // This starts a simple search for an emoticon.
    client.search(":)");

    // To design more complex searches, see the the API documentation here:
    // https://developer.twitter.com/en/docs/tweets/search/api-reference/get-search-tweets
    // and use the ofxTwitter::SearchQuery object like this:
    //
    //    ofxTwitter::SearchQuery query(":)");
    //    query.setGeoCode(41.8781, -87.6298, 10, ofxTwitter::SearchQuery::UNITS_MILES);
    //    query.setLanguage("en");
    //    client.search(query);
    //

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

    ofDrawBitmapStringHighlight(ss.str(), 14, 14);
}


void ofApp::onStatus(const ofxTwitter::Status& status)
{
    count++;
    ofLogNotice("ofApp::onStatus") << "Text: " << status.text();

    if (status.isRetweet())
    {
        ofLogNotice("ofApp::onStatus") << "\tOriginal mesage: " << status.retweetedStatus()->text();
    }
}


void ofApp::onError(const ofxTwitter::Error& error)
{
    ofLogError("ofApp::onError") << "Error: " << error.code() << " " << error.message();
}


void ofApp::onException(const std::exception& notice)
{
    ofLogError("ofApp::onException") << "Exception: " << notice.what();
}


void ofApp::onMessage(const ofJson& json)
{
    // This is the raw message json and is ignored here.
}
