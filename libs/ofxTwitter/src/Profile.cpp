//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


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
