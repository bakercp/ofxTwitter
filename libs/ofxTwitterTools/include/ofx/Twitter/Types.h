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


#pragma once


#include <stdint.h>
#include <string>
#include <map>
#include <set>
#include <vector>


namespace ofx {
namespace Twitter {


class BaseUser
{
public:
    BaseUser();
    BaseUser(int64_t is, const std::string& screenName);

    virtual ~BaseUser();

    /// \returns the user id.
    int64_t id() const;

    /// \returns the user screen name.
    std::string screenName() const;

private:
    /// \brief The user id.
    int64_t _id = -1;

    /// \brief The user screen name.
    std::string _screenName;

    friend class Deserializer;
};


class BaseNamedUser: public BaseUser
{
public:
    BaseNamedUser();

    BaseNamedUser(int64_t ID,
                  const std::string& screenName,
                  const std::string& name);

    virtual ~BaseNamedUser();

    std::string name() const;

private:
    std::string _name;

    friend class Deserializer;
};


typedef std::set<std::string> Contries;
typedef std::map<std::string, std::string> Annotations;
typedef std::vector<BaseNamedUser> Contributors;


} } // namespace ofx::Twitter
