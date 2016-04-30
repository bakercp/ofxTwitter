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


#include "ofx/Twitter/Error.h"
#include "ofLog.h"


namespace ofx {
namespace Twitter {


Error::Error()
{
}


Error::Error(int64_t code, const std::string& message):
    _code(code),
    _message(message)
{
}


Error::~Error()
{
}


int64_t Error::code() const
{
    return _code;
}


std::string Error::message() const
{
    return _message;
}


Error Error::fromJSON(const ofJson& json)
{
    Error error;

    auto iter = json.cbegin();
    while (iter != json.cend())
    {
        const auto& key = iter.key();
        const auto& value = iter.value();

        if (key == "code") error._code = value;
        else if (key == "message") error._message = value;
        else ofLogWarning("Error::fromJSON") << "Unknown key: " << key;

        ++iter;
    }

    return error;
}


} } // namespace ofx::Twitter
