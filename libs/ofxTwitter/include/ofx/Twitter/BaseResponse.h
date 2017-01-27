//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include <vector>
#include "ofx/HTTP/BaseResponse.h"
#include "ofx/Twitter/Error.h"


namespace ofx {
namespace Twitter {


template <typename RequestType>
class BaseResponse: public HTTP::BufferedResponse<RequestType>
{
public:
    using HTTP::BufferedResponse<RequestType>::BufferedResponse;

    virtual ~BaseResponse()
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
    virtual void parseJSON(const ofJson& json)
    {
    }

    std::vector<Error> _errors;

};


} } // namespace ofx::Twitter
