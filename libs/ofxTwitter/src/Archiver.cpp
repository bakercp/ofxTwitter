//
// Copyright (c) 2019 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/Twitter/Archiver.h"


namespace ofx {
namespace Twitter {


Archiver::Archiver():
    _exitListener(ofEvents().exit.newListener(this, &Archiver::_onExit))
{
}


Archiver::~Archiver()
{
}


//void Archiver::attach(const SearchClient& client)
//{
//        client.onMessage.new
//
//}
//
//
//void Archiver::attach(const SearchClient& client)
//{
//    client.onMessage.new
//
//}


void Archiver::onMessage(void* sender, const ofJson& json)
{

}

void Archiver::_onExit(ofEventArgs& args)
{

}


void Archiver::_writeToDisk()
{

}


} } // namespace ofx::Twitter
