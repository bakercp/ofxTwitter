//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/Twitter/Place.h"


namespace ofx {
namespace Twitter {


Place::Place()
{
}


Place::~Place()
{
}


Place::Attributes Place::attributes() const
{
    return _attributes;
}


Geo::CoordinateBounds Place::boundingBox() const
{
    return _boundingBox;
}


std::string Place::country() const
{
    return _country;
}


std::string Place::countryCode() const
{
    return _countryCode;
}


std::string Place::fullName() const
{
    return _fullName;
}


std::string Place::id() const
{
    return _id;
}


std::string Place::name() const
{
    return _name;
}


std::string Place::placeType() const
{
    return _placeType;
}


std::string Place::url() const
{
    return _url;
}


Place Place::fromJSON(const ofJson& json)
{
    Place place;

    auto iter = json.cbegin();
    while (iter != json.cend())
    {
        const auto& key = iter.key();
        const auto& value = iter.value();

        if (key == "attributes")
        {
            auto _iter = value.cbegin();
            while (_iter != value.cend())
            {
                const auto& _key = _iter.key();
                const auto& _value = _iter.value();

                place._attributes.insert(std::make_pair(_key, _value.get<std::string>()));

                ++_iter;
            }
        }
        else if (key == "bounding_box")
        {
            auto _iter = value.cbegin();
            while (_iter != value.cend())
            {
                const auto& _key = _iter.key();
                const auto& _value = _iter.value();

                if (_key == "type")
                {
                    if (_value != "Polygon")
                    {
                        ofLogWarning("Place::fromJSON") << "Unknown bounding box type: " << _value;
                    }
                }
                else if (_key == "coordinates")
                {
                    place._boundingBox = Geo::CoordinateBounds(Geo::Coordinate(_value[0][0][1], _value[0][0][0]),
                                                               Geo::Coordinate(_value[0][3][1], _value[0][3][0]));
                }
                else ofLogWarning("Place::fromJSON") << "Unknown bounding box key: " << _key << " / " << _value;

                ++_iter;
            }
        }
        else if (key == "country") place._country = value;
        else if (key == "country_code") place._countryCode = value;
        else if (key == "id") place._id = value;
        else if (key == "name") place._name = value;
        else if (key == "full_name") place._fullName = value;
        else if (key == "place_type") place._placeType = value;
        else if (key == "url") place._url = value;
        else ofLogWarning("Place::fromJSON") << "Unknown key: " << key << std::endl << value;

        ++iter;
    }

    return place;
}


} } // namespace ofx::Twitter
