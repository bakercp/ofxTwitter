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
    // Developers must get their credentials after creating an app at https://apps.twitter.com
    client.setCredentialsFromFile("credentials.json");

    // Set the polling interval for 6 seconds.
    client.setPollingInterval(6000);

    // This starts the search.
    // You can test and build REST searches here http://search.twitter.com.
    client.search(":) filter:twimg");

    // To design more complex searches, see the the API documentation here:
    // https://dev.twitter.com/rest/public/search and use the
    // ofxTwitter::SearchQuery object like this:
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

    std::stringstream ss;
    ss << "  Received: " << count << std::endl;
    ss << "  See downloaded images in" << std::endl;
    ss << "  the bin/data directory.";

    ofDrawBitmapStringHighlight(ss.str(), 14, 14);
}


void ofApp::onStatus(const ofxTwitter::Status& status)
{
    count++;

    for (auto e: status.extendedEntities().mediaEntities())
    {
        if (e.type() == ofxTwitter::MediaEntity::Type::PHOTO)
        {
            std::string filename = e.mediaFilename();
            ofSaveURLAsync(e.mediaURL(), filename);
            ofLogNotice("ofApp::onStatus") << "Downloading " << filename;
        }
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
