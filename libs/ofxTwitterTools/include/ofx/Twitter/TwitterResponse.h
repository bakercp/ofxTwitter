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


#include <vector>
#include "ofx/HTTP/BaseResponse.h"
#include "ofx/Twitter/Error.h"


namespace ofx {
namespace Twitter {


template <typename RequestType>
class TwitterResponse: public HTTP::BufferedResponse<RequestType>
{
public:
    using HTTP::BufferedResponse<RequestType>::BufferedResponse;

    virtual ~TwitterResponse()
    {
    }

    std::vector<Error> errors() const
    {
        return _errors;
    }

protected:
    virtual void parseBuffer() override
    {
        ofJson json;

        try
        {
            json = ofJson::parse(HTTP::BufferedResponse<RequestType>::getBuffer());

            auto iter = json.find("errors");

            if (iter != json.end())
            {
                for (auto& error: iter.value())
                {
                    _errors.push_back(Error::fromJSON(error));
                }

                // Remove the errors.
                json.erase(iter);
            }
            
            parseJSON(json);

        }
        catch (const std::exception& exc)
        {
            ofLogError("TwitterResponse::json") << "Unable to interpret data as json: " << exc.what();
        }

    }

    /// \brief Subclasses can further parse JSON data.
    /// \param json The JSON Data to parse.
    virtual void parseJSON(ofJson& json)
    {
    }

    std::vector<Error> _errors;

};


} } // namespace ofx::Twitter
