//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include <string>


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
    bool _useBackgroundImage = false;
    std::string _backgroundImageUrl;
    std::string _backgroundImageUrlHttps;
    bool _backgroundTile = false;

    // banner
    std::string _bannerUrl;

    // sidebar
    std::string _sidebarBorderColorHex;
    std::string _sidebarFillColorHex;
    std::string _sidebarTextColorHex;

};


} } // namespace ofx::Twitter
