//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/Twitter/Notices.h"


namespace ofx {
namespace Twitter {


const std::string StatusDeletedNotice::JSON_KEY = "delete";


int64_t StatusDeletedNotice::userId() const
{
    return _userId;
}


int64_t StatusDeletedNotice::statusId() const
{
    return _statusId;
}


uint64_t StatusDeletedNotice::timestamp() const
{
    return _timestamp;
}


ofJson StatusDeletedNotice::json() const
{
    return _json;
}


StatusDeletedNotice StatusDeletedNotice::fromJSON(const ofJson& json)
{
    StatusDeletedNotice notice;
    notice._json = json;
    notice._userId = json["status"]["id"];
    notice._statusId = json["status"]["user_id"];
    notice._timestamp = std::stoull(json["timestamp_ms"].get<std::string>());
    return notice;
}


const std::string LocationDeletedNotice::JSON_KEY = "scrub_geo";


int64_t LocationDeletedNotice::userId() const
{
    return _userId;
}

    
int64_t LocationDeletedNotice::upToStatusId() const
{
    return _upToStatusId;
}


LocationDeletedNotice LocationDeletedNotice::fromJSON(const ofJson& json)
{
    LocationDeletedNotice notice;
    notice._json = json;
    notice._userId = json["id"];
    notice._upToStatusId = json["up_to_status_id"];
    return notice;
}


const std::string LimitNotice::JSON_KEY = "limit";


uint64_t LimitNotice::track() const
{
    return _track;
}


ofJson LimitNotice::json() const
{
    return _json;
}


LimitNotice LimitNotice::fromJSON(const ofJson& json)
{
    LimitNotice notice;
    notice._json = json;
    notice._track = json["track"];
    return notice;
}


const std::string StatusWithheldNotice::JSON_KEY = "status_withheld";


int64_t StatusWithheldNotice::userId() const
{
    return _userId;
}


int64_t StatusWithheldNotice::statusId() const
{
    return _statusId;
}


std::vector<std::string> StatusWithheldNotice::countries() const
{
    return _countries;
}


ofJson StatusWithheldNotice::json() const
{
    return _json;
}


StatusWithheldNotice StatusWithheldNotice::fromJSON(const ofJson& json)
{
    StatusWithheldNotice notice;
    notice._json = json;
    notice._statusId = json["id"];
    notice._userId = json["user_id"];

    for (auto country: json["withheld_in_countries"])
    {
        notice._countries.push_back(country);
    }

    return notice;
}


const std::string UserWithheldNotice::JSON_KEY = "user_withheld";


int64_t UserWithheldNotice::userId() const
{
    return _userId;
}


std::vector<std::string> UserWithheldNotice::countries() const
{
    return _countries;
}


ofJson UserWithheldNotice::json() const
{
    return _json;
}


UserWithheldNotice UserWithheldNotice::fromJSON(const ofJson& json)
{
    UserWithheldNotice notice;
    notice._json = json;
    notice._userId = json["id"];

    for (auto country: json["withheld_in_countries"])
    {
        notice._countries.push_back(country);
    }
    return notice;
}


const std::string DisconnectNotice::JSON_KEY = "disconnect";


int64_t DisconnectNotice::code() const
{
    return _code;
}


std::string DisconnectNotice::streamName() const
{
    return _streamName;
}


std::string DisconnectNotice::reason() const
{
    return _reason;
}


ofJson DisconnectNotice::json() const
{
    return _json;
}


DisconnectNotice DisconnectNotice::fromJSON(const ofJson& json)
{
    DisconnectNotice notice;
    notice._json = json;
    notice._code = json["code"];
    notice._streamName = json["stream_name"];
    notice._reason = json["reason"];
    return notice;
}


const std::string StallWarning::JSON_KEY = "warning";


std::string StallWarning::code() const
{
    return _code;
}


std::string StallWarning::message() const
{
    return _message;
}


double StallWarning::percentFull() const
{
    return _percentFull;
}


ofJson StallWarning::json() const
{
    return _json;
}


StallWarning StallWarning::fromJSON(const ofJson& json)
{
    StallWarning notice;
    notice._json = json;
    notice._code = json["code"];
    notice._message = json["message"];
    notice._percentFull = json["percent_full"];
    return notice;
}


} } // namespace ofx::Twitter
