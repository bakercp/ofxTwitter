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


#include "ofx/Twitter/Tweet.h"


namespace ofx {
namespace Twitter {


Tweet::Tweet()
{
}


Tweet::~Tweet()
{
}


Annotations Tweet::annotations() const
{
    return _annotations;
}


Contributors Tweet::contributors() const
{
    return _contributors;
}


const Geo::Coordinate* Tweet::coordinates() const
{
    return _coordinates.get();
}


int64_t Tweet::id() const
{
    return _id;
}


Poco::DateTime Tweet::createdAt() const
{
    return _createdAt;
}


const User* Tweet::user() const
{
    return _user.get();
}


std::string Tweet::text() const
{
    return _text;
}


} } // namespace ofx::Twitter
