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

    ofxTwitter::RESTClient client;

};
