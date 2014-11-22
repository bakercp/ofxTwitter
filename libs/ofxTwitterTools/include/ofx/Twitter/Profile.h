// =============================================================================
//
// Copyright (c) 2009-2013 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


#pragma once


#include <stdint.h>
#include <string>
#include <vector>
#include <set>
#include "Poco/DateTime.h"
#include "Poco/Nullable.h"
#include "ofx/Twitter/Types.h"
#include "ofx/Twitter/Entities.h"
//#include "ofx/Twitter/Tweet.h"


namespace ofx {
namespace Twitter {


class Profile
{
public:
    Profile();

    Profile(const std::string& backgroundColorHex,
            const std::string& linkColorHex,
            bool useBackgroundImage,
            const std::string& backgroundImageUrl,
            const std::string& backgroundImageUrlHttps,
            bool backgroundTile,
            const std::string& bannerUrl,
            const std::string& sidebarBorderColorHex,
            const std::string& sidebarFillColorHex,
            const std::string& sidebarTextColorHex);

    virtual ~Profile();

    void setBackgroundColorHex(const std::string& backgroundColorHex);

    // TODO: finish setters

    std::string getBackgroundColorHex() const;

    std::string getLinkColorHex() const;

    bool useBackgroundImage() const;

    std::string getBackgroundImageUrl() const;

    std::string getBackgroundImageUrlHttps() const;

    bool getBackgroundTile() const;

    std::string getBannerUrl() const;

private:
    // colors
    std::string _backgroundColorHex;
    std::string _linkColorHex;

    // background image
    bool _useBackgroundImage;
    std::string _backgroundImageUrl;
    std::string _backgroundImageUrlHttps;
    bool _backgroundTile;

    // banner
    std::string _bannerUrl;

    // sidebar
    std::string _sidebarBorderColorHex;
    std::string _sidebarFillColorHex;
    std::string _sidebarTextColorHex;

};


} } // namespace ofx::Twitter
