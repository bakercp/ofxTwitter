//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include <map>
#include <string>
#include "ofJson.h"
#include "ofx/Geo/CoordinateBounds.h"


namespace ofx {
namespace Twitter {


/// \brief The Twitter Place object.
///
/// Places are specific, named locations with corresponding geo coordinates.
/// They can be attached to Tweets by specifying a place_id when tweeting.
/// Tweets associated with places are not necessarily issued from that location
/// but could also potentially be about that location. Places can be searched
/// for. Tweets can also be found by place_id.
///
/// Places also have an attributes field that further describes a Place. These
/// attributes are more convention rather than standard practice, and reflect
/// information captured in the Twitter places database. See Place Attributes
/// for more information.
///
/// \sa https://dev.twitter.com/overview/api/places
class Place
{
public:
    /// \brief A typedef representing a Place's Attribuets.
    typedef std::map<std::string, std::string> Attributes;

    /// \brief Create a default Place.
    Place();

    /// \brief Destroy the Place object.
    virtual ~Place();

    /// \brief Get Place attributes.
    ///
    /// Place Attributes are metadata about places. An attribute is a key-value
    /// pair of arbitrary strings, but with some conventions.
    ///
    /// Attributes are provided when the place was created in the Twitter places
    /// database.
    ///
    /// \returns the place attributes, if available or an empty map.
    Attributes attributes() const;

    /// \brief The bounding box that encloses this Place.
    /// \returns a bounding box.
    Geo::CoordinateBounds boundingBox() const;

    /// \returns the name of the country containing this Place.
    std::string country() const;

    /// \returns the shortened country code representing the country containing this Place.
    std::string countryCode() const;

    /// \returns the full human-readable representation of the Place’s name.
    std::string fullName() const;

    /// \returns the ID representing this place.
    /// \note This is represented as a string, not an integer.
    std::string id() const;

    /// \returns a short human-readable representation of the Place’s name.
    std::string name() const;

    /// \returns The type of location represented by this place
    std::string placeType() const;

    /// \returns URL representing the location of additional place metadata for this place.
    std::string url() const;

    /// \brief Extract the Place from JSON.
    /// \param json The source JSON.
    /// \returns the extracted Place.
    static Place fromJSON(const ofJson& json);

private:
    /// \brief Place attributes.
    Attributes _attributes;

    /// \brief The bounding box that encloses this Place.
    Geo::CoordinateBounds _boundingBox;

    /// \brief Name of the country containing this Place.
    std::string _country;

    /// \brief Shortened country code representing the country containing this Place.
    std::string _countryCode;

    /// \brief Full human-readable representation of the Place’s name.
    std::string _fullName;

    /// \brief ID representing this place.
    /// \note This is represented as a string, not an integer.
    std::string _id;

    /// \brief Short human-readable representation of the Place’s name.
    std::string _name;

    /// \brief The type of location represented by this place
    std::string _placeType;

    /// \brief URL representing the location of additional place metadata for this place.
    std::string _url;

};


} } // namespace ofx::Twitter
