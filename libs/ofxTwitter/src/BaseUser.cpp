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


#include "ofx/Twitter/BaseUser.h"
#include "ofLog.h"


namespace ofx {
namespace Twitter {


BaseUser::BaseUser()
{
}


BaseUser::BaseUser(int64_t id, const std::string& screenName):
    _id(id),
    _screenName(screenName)
{
}


BaseUser::~BaseUser()
{
}


int64_t BaseUser::id() const
{
    return _id;
}


std::string BaseUser::screenName() const
{
    return _screenName;
}


BaseNamedUser::BaseNamedUser()
{
}


BaseNamedUser::BaseNamedUser(int64_t id,
                             const std::string& screenName,
                             const std::string& name):
    BaseUser(id, screenName),
    _name(name)
{
}


BaseNamedUser::~BaseNamedUser()
{
}


std::string BaseNamedUser::name() const
{
    return _name;
}


} } // namespace ofx::Twitter
