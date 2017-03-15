//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofApp.h"


void ofApp::setup()
{
     // ofSetLogLevel(OF_LOG_VERBOSE);

    // First we load credentials from a file. These can also be loaded using
    // the other setCredentials*(...) methods.
    //
    // Developers must get their credentials after creating an app at
    // https://apps.twitter.com.
    client.setCredentialsFromFile("NetworkedObject.json");

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
    query.setTracks({":)", ":("});

    // Start filter query.
    client.filter(query);

}


void ofApp::update()
{
    //client.syncEvents();
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

    ss << "% Received: " <<  received;

    ofDrawBitmapStringHighlight(ss.str(), 14, 20);
}


bool ofApp::onConnect(const void* source)
{
    ofLogNotice("ofApp::onConnect") << "Connected." << std::endl;
    return true;
}


bool ofApp::onDisconnect(const void* source)
{
    ofLogNotice("ofApp::onDisconnect") << "Disconnected." << std::endl;
    return true;
}


bool ofApp::onStatus(const void* source, const ofxTwitter::Status& status)
{
    count++;
    ofLogNotice("ofApp::onStatus") << "Text: " << status.text();
    ofLogNotice("ofApp::onStatus") << "Coordinates: " << (status.coordinates() ? ofToString(status.coordinates()) : "NONE");
    ofLogNotice("ofApp::onStatus") << "Place: " << (status.place() ? ofToString(status.place()->fullName()) : "NONE");
    return true;
}


bool ofApp::onStatusDeletedNotice(const void* source, const ofxTwitter::StatusDeletedNotice& notice)
{
    ofLogNotice("ofApp::onStatusDeletedNotice") << "Status deleted.";
    return true;
}


bool ofApp::onLocationDeletedNotice(const void* source, const ofxTwitter::LocationDeletedNotice& notice)
{
    ofLogNotice("ofApp::onLocationDeletedNotices") << "Location scrubbed.";
    return true;
}


bool ofApp::onLimitNotice(const void* source, const ofxTwitter::LimitNotice& notice)
{
    countMissed += notice.track();
    ofLogNotice("ofApp::onLimitNotice") << "Limited: " << notice.track();
    return true;
}


bool ofApp::onStatusWithheldNotice(const void* source, const ofxTwitter::StatusWithheldNotice& notice)
{
    ofLogNotice("ofApp::onLimitNotice") << "Status witheld.";
    return true;
}


bool ofApp::onUserWitheldNotice(const void* source, const ofxTwitter::UserWithheldNotice& notice)
{
    ofLogNotice("ofApp::onUserWitheldNotice") << "User witheld.";
    return true;
}


bool ofApp::onDisconnectNotice(const void* source, const ofxTwitter::DisconnectNotice& notice)
{
    ofLogNotice("ofApp::onDisconnectNotice") << "Disconnect notice: " << notice.reason();
    return true;
}


bool ofApp::onStallWarning(const void* source, const ofxTwitter::StallWarning& notice)
{
    ofLogNotice("ofApp::onStallWarning") << "Stall warning: " << notice.message();
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
