//
// Copyright (c) 2019 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include <string>
#include "ofx/Twitter/SearchClient.h"
#include "ofx/Twitter/StreamingClient.h"


namespace ofx {
namespace Twitter {


/// \brief An archiver.
class Archiver
{
public:
    Archiver();
    virtual ~Archiver();

//    template<class ClientType>
//    void attach(const ClientType& client)
//    {
//        client.onMessage.
//    }

//    template<class ClientType>
//    void detatch(const ClientType& client)
//    {
//
//    }

    void onMessage(void* sender, const ofJson& json);

private:
    void _onExit(ofEventArgs& args);
    void _writeToDisk();

    IO::ThreadChannel<std::pair<ofJson, Status>> _statusChannel;

    std::map<ofJson, std::vector<ofJson>> _statuses;

    ofEventListener _exitListener;

};


} } // namespace ofx::Twitter
