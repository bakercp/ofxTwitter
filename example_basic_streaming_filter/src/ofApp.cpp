//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofApp.h"


void ofApp::setup()
{
    // First we load credentials from a file. These can also be loaded using
    // the other setCredentials*(...) methods.
    //
    // Developers must get their credentials after creating an app at
    // https://apps.twitter.com.
    client.setCredentialsFromFile("credentials.json");

    
    // Register all available streaming events.
    // Alternatively, one can register events individually.
    //
    // In default mode all events are sent during the update() event loop.
    client.registerStreamingEvents(this);

    // Create a bounding box for San Francisco.
    ofxGeo::CoordinateBounds sanFranciscoBounds(ofxGeo::Coordinate(37.8, -122.75),
                                                ofxGeo::Coordinate(36.8, -121.75));


    // Create a bounding box for New York.
    ofxGeo::CoordinateBounds newYorkBounds(ofxGeo::Coordinate(41, -74),
                                           ofxGeo::Coordinate(40, -73));

    // Create a filter query.
    ofxTwitter::FilterQuery query;

    // Set the bouning boxes of interest.

    // Note that bounding boxes do not act as filters for other filter
    // parameters. For example the locations below match any Tweets containing
    // track terms (even non-geo Tweets) OR coming from the San Francisco /
    // New York area.
    //
    // query.setLocations({ sanFranciscoBounds, newYorkBounds });

    // Track two emoji.
    // Read more about query terms here:
    // https://dev.twitter.com/streaming/overview/request-parameters
    query.setTracks({":(", ":)"});

    // Start filter query.
    client.filter(query);

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


void ofApp::onConnect()
{
    ofLogNotice("ofApp::onConnect") << "Connected.";
}


void ofApp::onDisconnect()
{
    ofLogNotice("ofApp::onDisconnect") << "Disconnected.";
}


void ofApp::onStatus(const ofxTwitter::Status& status)
{
    count++;
    ofLogNotice("ofApp::onStatus") << "Text: " << status.text();
    ofLogNotice("ofApp::onStatus") << "\tCoordinates: " << (status.coordinates() ? ofToString(status.coordinates()) : "NONE");
    ofLogNotice("ofApp::onStatus") << "\tPlace: " << (status.place() ? ofToString(status.place()->fullName()) : "NONE");
}


void ofApp::onStatusDeletedNotice(const ofxTwitter::StatusDeletedNotice& notice)
{
    ofLogNotice("ofApp::onStatusDeletedNotice") << "Status deleted.";
}


void ofApp::onLocationDeletedNotice(const ofxTwitter::LocationDeletedNotice& notice)
{
    ofLogNotice("ofApp::onLocationDeletedNotices") << "Location scrubbed.";
}


void ofApp::onLimitNotice(const ofxTwitter::LimitNotice& notice)
{
    countMissed += notice.track();
    ofLogNotice("ofApp::onLimitNotice") << "Limited: " << notice.track();
}


void ofApp::onStatusWithheldNotice(const ofxTwitter::StatusWithheldNotice& notice)
{
    ofLogNotice("ofApp::onLimitNotice") << "Status witheld.";
}


void ofApp::onUserWitheldNotice(const ofxTwitter::UserWithheldNotice& notice)
{
    ofLogNotice("ofApp::onUserWitheldNotice") << "User witheld.";
}


void ofApp::onDisconnectNotice(const ofxTwitter::DisconnectNotice& notice)
{
    ofLogNotice("ofApp::onDisconnectNotice") << "Disconnect notice: " << notice.reason();
}


void ofApp::onStallWarning(const ofxTwitter::StallWarning& notice)
{
    ofLogNotice("ofApp::onStallWarning") << "Stall warning: " << notice.message();
}


void ofApp::onException(const std::exception& notice)
{
    ofLogError("ofApp::onException") << "Exception: " << notice.what();
}


void ofApp::onMessage(const ofJson& json)
{
    // Ignoring the raw message.
}
