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
    client.setCredentialsFromFile("credentials.json");

    // Register all available streaming events. Alternatively, one can register
    // events individually.
    client.registerStreamingEvents(this);

    // Set up listeners.
    client.filter({"😬", "😬", "😁", "😂", "😃", "😄", "😅", "😆", "😇", "😉", "😊", "🙂", "🙃", "☺️", "😋", "😌", "😍", "😘", "😗", "😙", "😚", "😜", "😝", "😛", "🤑", "🤓", "😎", "🤗", "😏", "😶", "😐", "😑", "😒", "🙄", "🤔", "😳", "😞", "😟", "😠", "😡", "😔", "😕", "🙁", "☹️", "😣", "😖", "😫", "😩", "😤", "😮", "😱", "😨", "😰", "😯", "😦", "😧", "😢", "😥 ", "😪", "😓", "😭", "😵", "😲", "🤐", "😷", "🤒", "🤕", "😴", "💤", "💩"});

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


void ofApp::onConnect()
{
    std::cout << "Connected." << std::endl;
}


void ofApp::onDisconnect()
{
    std::cout << "Disconnected." << std::endl;
}


void ofApp::onStatus(const ofxTwitter::Status& status)
{
    count++;
    std::cout << status.text() << std::endl;
}


void ofApp::onStatusDeletedNotice(const ofxTwitter::StatusDeletedNotice& notice)
{
     std::cout << "Status deleted." << std::endl;
}


void ofApp::onLocationDeletedNotice(const ofxTwitter::LocationDeletedNotice& notice)
{
    std::cout << "Location scrubbed." << std::endl;
}


void ofApp::onLimitNotice(const ofxTwitter::LimitNotice& notice)
{
    countMissed += notice.track();
    std::cout << "Limited: " << notice.track() << std::endl;
}


void ofApp::onStatusWithheldNotice(const ofxTwitter::StatusWithheldNotice& notice)
{
    std::cout << "Status witheld." << std::endl;
}


void ofApp::onUserWitheldNotice(const ofxTwitter::UserWithheldNotice& notice)
{
    std::cout << "User witheld." << std::endl;
}


void ofApp::onDisconnectNotice(const ofxTwitter::DisconnectNotice& notice)
{
    std::cout << "Disconnect notice: " << notice.reason() << std::endl;
}


void ofApp::onStallWarning(const ofxTwitter::StallWarning& notice)
{
    std::cout << "Stall warning: " << notice.message() << std::endl;
}


void ofApp::onException(const std::exception& notice)
{
    std::cout << "Exception: " << notice.what() << std::endl;
}


void ofApp::onMessage(const ofJson& json)
{
    // Skip.
}
