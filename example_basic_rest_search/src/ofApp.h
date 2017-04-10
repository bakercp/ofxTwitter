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

    void onStatus(const ofxTwitter::Status& status);
    void onError(const ofxTwitter::Error& error);
    void onException(const std::exception& exception);
    void onMessage(const ofJson& json);

    ofxTwitter::SearchClient client;

    uint64_t count = 0;
    uint64_t countMissed = 0;

};
