// =============================================================================
//
// Copyright (c) 2009-2016 Christopher Baker <http://christopherbaker.net>
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


#include "ofx/Twitter/User.h"


namespace ofx {
namespace Twitter {


User::User()
{
}

User::User(int64_t ID,
           const std::string& screenName,
           const std::string& name):
    BaseNamedUser(ID, screenName, name)
{
}


User::~User()
{
}


bool User::areContributorsEnabled() const
{
    return _contributorsEnabled;
}


Poco::DateTime User::createdAt() const
{
    return _createdAt;
}


bool User::hasDefaultProfile() const
{
    return _hasDefaultProfile;
}


bool User::hasDefaultProfileImage() const
{
    return _hasDefaultProfileImage;
}


std::string User::description() const
{
    return _description;
}


Entities User::entities() const
{
    return _entities;
}


int User::favouritesCount() const
{
    return _favouritesCount;
}


bool User::wasFollowRequestSent() const
{
    return _followRequestSent;
}


int User::followersCount() const
{
    return _followersCount;
}


int User::friendsCount() const
{
    return _friendsCount;
}


bool User::isGeoEnabled() const
{
    return _isGeoEnabled;
}


bool User::isTranslator() const
{
    return _isTranslator;
}


std::string User::language() const
{
    return _language;
}


int User::listedCount() const
{
    return _listedCount;
}


std::string User::location() const
{
    return _location;
}


Profile User::profile() const
{
    return _profile;
}


bool User::isProtected() const
{
    return _isProtected;
}


bool User::showsAllInlineMedia()
{
    return _showsAllInlineMedia;
}


//Poco::Nullable<Tweet> User::getStatus() const
//{
//    return _status;
//}


int User::statusesCount() const
{
    return _statusesCount;
}


std::string User::timeZone() const
{
    return _timeZone;
}


std::string User::url() const
{
    return _url;
}


int User::utcOffset() const
{
    return _UTCOffset;
}


bool User::isVerified() const
{
    return _isVerified;
}


Contries User::withheldInCountries() const
{
    return _withheldInCountries;
}
    

User::WithheldScope User::withheldScope() const
{
    return _withheldScope;
}


} } // namespace ofx::Twitter
