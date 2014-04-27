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


#include "ofx/Twitter/Profile.h"


namespace ofx {
namespace Twitter {


Profile::Profile():
    _backgroundColorHex("FFFFFF"),
    _linkColorHex("FFFFFF"),
    _useBackgroundImage(false),
    _backgroundImageUrl(""),
    _backgroundImageUrlHttps(""),
    _backgroundTile(false),
    _bannerUrl(""),
    _sidebarBorderColorHex("000000"),
    _sidebarFillColorHex("FFFFFF"),
    _sidebarTextColorHex("888888")
{
}


Profile::Profile(const std::string& backgroundColorHex,
                 const std::string& linkColorHex,
                 bool useBackgroundImage,
                 const std::string& backgroundImageUrl,
                 const std::string& backgroundImageUrlHttps,
                 bool backgroundTile,
                 const std::string& bannerUrl,
                 const std::string& sidebarBorderColorHex,
                 const std::string& sidebarFillColorHex,
                 const std::string& sidebarTextColorHex):
    _backgroundColorHex(backgroundImageUrl),
    _linkColorHex(linkColorHex),
    _useBackgroundImage(useBackgroundImage),
    _backgroundImageUrl(backgroundImageUrl),
    _backgroundImageUrlHttps(backgroundImageUrlHttps),
    _backgroundTile(backgroundTile),
    _bannerUrl(bannerUrl),
    _sidebarBorderColorHex(sidebarBorderColorHex),
    _sidebarFillColorHex(sidebarFillColorHex),
    _sidebarTextColorHex(sidebarTextColorHex)
{
}


Profile::~Profile()
{
}


void Profile::setBackgroundColorHex(const std::string& backgroundColorHex)
{
    _backgroundColorHex = backgroundColorHex;
}

// TODO: finish setters

std::string Profile::getBackgroundColorHex() const
{
    return _backgroundColorHex;
}


std::string Profile::getLinkColorHex() const
{
    return _linkColorHex;
}


bool Profile::useBackgroundImage() const
{
    return _useBackgroundImage;
}


std::string Profile::getBackgroundImageUrl() const
{
    return _backgroundImageUrl;
}


std::string Profile::getBackgroundImageUrlHttps() const
{
    return _backgroundImageUrlHttps;
}


bool Profile::getBackgroundTile() const
{
    return _backgroundTile;
}


std::string Profile::getBannerUrl() const
{
    return _bannerUrl;
}
    

} } // namespace ofx::Twitter
