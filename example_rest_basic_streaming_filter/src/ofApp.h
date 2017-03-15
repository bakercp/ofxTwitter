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
    void setup() override;
    void update() override;
    void draw() override;

    bool onConnect(const void* source);
    bool onDisconnect(const void* source);
    bool onStatus(const void* source, const ofxTwitter::Status& status);
    bool onStatusDeletedNotice(const void* source, const ofxTwitter::StatusDeletedNotice& notice);
    bool onLocationDeletedNotice(const void* source, const ofxTwitter::LocationDeletedNotice& notice);
    bool onLimitNotice(const void* source, const ofxTwitter::LimitNotice& notice);
    bool onStatusWithheldNotice(const void* source, const ofxTwitter::StatusWithheldNotice& notice);
    bool onUserWitheldNotice(const void* source, const ofxTwitter::UserWithheldNotice& notice);
    bool onDisconnectNotice(const void* source, const ofxTwitter::DisconnectNotice& notice);
    bool onStallWarning(const void* source, const ofxTwitter::StallWarning& notice);
    bool onException(const void* source, const std::exception& exception);
    bool onMessage(const void* source, const ofJson& json);

    ofxTwitter::StreamingClient client;

    uint64_t count = 0;
    uint64_t countMissed = 0;

};
