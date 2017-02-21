//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/Twitter/StreamingQuery.h"
#include "ofx/HTTP/HTTPUtils.h"


namespace ofx {
namespace Twitter {


StreamingQuery::~StreamingQuery()
{
}


void StreamingQuery::setDelimited(Delimited delimited)
{
    switch (delimited)
    {
        case Delimited::DEFAULT:
            erase("delimited");
            return;
        case Delimited::LENGTH:
            set("delimited", "length");
            return;
    }
}


void StreamingQuery::setStallWarnings(bool stallWarnings)
{
    if (stallWarnings)
        set("stall_warnings", "true");
    else
        erase("stall_warnings");
}


void StreamingQuery::setFilterLevel(FilterLevel filterLevel)
{
    switch (filterLevel)
    {
        case FilterLevel::DEFAULT:
            erase("filter_level");
            return;
        case FilterLevel::MEDIUM:
            set("filter_level", "medium");
            return;
        case FilterLevel::LOW:
            set("filter_level", "low");
            return;
        case FilterLevel::NONE:
            set("filter_level", "none");
            return;
    }
}


void StreamingQuery::setLanguage(const std::string& language)
{
    setLanguages({ language });
}


void StreamingQuery::setLanguages(const std::vector<std::string>& languages)
{
    if (languages.empty())
        erase("language");
    else
        set("language", HTTP::HTTPUtils::join(languages, ","));
}

    
} } // namespace ofx::Twitter
