//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/Twitter/FilterQuery.h"
#include "ofx/HTTP/HTTPUtils.h"


namespace ofx {
namespace Twitter {


BaseFilterQuery::~BaseFilterQuery()
{
}


void BaseFilterQuery::setTrack(const std::string& track)
{
    setTracks({ track });
}

    
void BaseFilterQuery::setTracks(const std::vector<std::string>& tracks)
{
    if (tracks.empty())
        erase("track");
    else
        set("track", HTTP::HTTPUtils::join(tracks, ","));
}


void BaseFilterQuery::setLocation(const Geo::CoordinateBounds& location)
{
    setLocations({ location });
}


void BaseFilterQuery::setLocations(const std::vector<Geo::CoordinateBounds>& locations)
{
    if (locations.empty())
    {
        erase("locations");
    }
    else
    {
        std::vector<double> values;

        for (auto& bound: locations)
        {
            values.push_back(bound.getSouthwest().getLongitude());
            values.push_back(bound.getSouthwest().getLatitude());
            values.push_back(bound.getNortheast().getLongitude());
            values.push_back(bound.getNortheast().getLatitude());
        }

        set("locations", HTTP::HTTPUtils::join(values, ","));
    }
}


const std::string FilterQuery::RESOURCE_URL = "https://stream.twitter.com/1.1/statuses/filter.json";


FilterQuery::~FilterQuery()
{
}


void FilterQuery::setFollow(const std::string& follow)
{
    setFollows({ follow });
}


void FilterQuery::setFollows(const std::vector<std::string>& follows)
{
    if (follows.empty())
        erase("follow");
    else
        set("follow", HTTP::HTTPUtils::join(follows, ","));
}




UserFilterQuery::~UserFilterQuery()
{
}


void UserFilterQuery::setReplies(bool replies)
{
    if (replies)
        set("replies", "all");
    else
        erase("replies");
}


void UserFilterQuery::setWith(With with)
{
    switch (with)
    {
        case With::DEFAULT:
            erase("with");
            return;
        case With::USERS:
            set("with", "users");
            return;
        case With::FOLLOWINGS:
            set("with", "followings");
            return;
    }
}



} } // namespace ofx::Twitter
