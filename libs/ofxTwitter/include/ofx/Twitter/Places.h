//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include <set>
#include <string>


namespace ofx {
namespace Twitter {


//    "place":
//    {
//        "attributes":{},
//        "bounding_box":
//        {
//            "coordinates":
//            [[
//              [-77.119759,38.791645],
//              [-76.909393,38.791645],
//              [-76.909393,38.995548],
//              [-77.119759,38.995548]
//              ]],
//            "type":"Polygon"
//        },
//        "country":"United States",
//        "country_code":"US",
//        "full_name":"Washington, DC",
//        "id":"01fbe706f872cb32",
//        "name":"Washington",
//        "place_type":"city",
//        "url": "http://api.twitter.com/1/geo/id/01fbe706f872cb32.json"
//    }

class Places
{
public:
    Places();
    virtual ~Places();

};


} } // namespace ofx::Twitter
