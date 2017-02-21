//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include "ofMain.h"
#include "ofxTwitter.h"


class ofApp: public ofBaseApp
{
public:
    void setup();
    void draw();

    void keyPressed(int key)
    {
        if (key == 'c')
        {
            client.sample();
        }
        else if (key == 'd')
        {
            client.waitForDisconnect();
        }
    }
    

    void onConnect();
    void onDisconnect();
    void onStatus(const ofxTwitter::Status& status);
    void onStatusDeletedNotice(const ofxTwitter::StatusDeletedNotice& notice);
    void onLocationDeletedNotice(const ofxTwitter::LocationDeletedNotice& notice);
    void onLimitNotice(const ofxTwitter::LimitNotice& notice);
    void onStatusWithheldNotice(const ofxTwitter::StatusWithheldNotice& notice);
    void onUserWitheldNotice(const ofxTwitter::UserWithheldNotice& notice);
    void onDisconnectNotice(const ofxTwitter::DisconnectNotice& notice);
    void onStallWarning(const ofxTwitter::StallWarning& notice);
    void onException(const std::exception& exception);
    void onMessage(const ofJson& json);

    ofxTwitter::StreamingClient client;

    uint64_t count = 0;
    uint64_t countMissed = 0;

};
