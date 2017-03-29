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

    bool onStatus(const void* source, const ofxTwitter::Status& status);
    bool onError(const void* source, const ofxTwitter::Error& error);
    bool onException(const void* source, const std::exception& exception);
    bool onMessage(const void* source, const ofJson& json);

    ofxTwitter::SearchClient client;

    uint64_t count = 0;
    uint64_t countMissed = 0;

};
