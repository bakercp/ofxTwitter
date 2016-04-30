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


#include "ofx/Twitter/Entities.h"
#include "ofLog.h"


namespace ofx {
namespace Twitter {


BaseIndexedEntity::BaseIndexedEntity(std::size_t startIndex,
                                     std::size_t endIndex):
    _startIndex(startIndex),
    _endIndex(endIndex)
{
}


BaseIndexedEntity::~BaseIndexedEntity()
{
}


std::size_t BaseIndexedEntity::startIndex() const
{
    return _startIndex;
}


std::size_t BaseIndexedEntity::endIndex() const
{
    return _endIndex;
}


HashTagEntity::HashTagEntity(const std::string& hashTag,
                             std::size_t startIndex,
                             std::size_t endIndex):
    BaseIndexedEntity(startIndex, endIndex),
    _hashTag(hashTag)
{
}


HashTagEntity::~HashTagEntity()
{
}


std::string HashTagEntity::hashTag() const
{
    return _hashTag;
}


std::string HashTagEntity::indexedText() const
{
    return _hashTag;
}


URLEntity::URLEntity(const std::string& url,
                     const std::string& displayURL,
                     const std::string& expandedURL,
                     std::size_t startIndex,
                     std::size_t endIndex):
    BaseIndexedEntity(startIndex, endIndex),
    _url(url),
    _displayURL(displayURL),
    _expandedURL(expandedURL)
{
}


URLEntity::~URLEntity()
{
}


std::string URLEntity::url() const
{
    return _url;
}


std::string URLEntity::displayURL() const
{
    return _displayURL;
}


std::string URLEntity::expandedURL() const
{
    return _expandedURL;
}


std::string URLEntity::indexedText() const
{
    return _url;
}


MediaEntitySize::MediaEntitySize(Type type,
                                 Resize resize,
                                 std::size_t width,
                                 std::size_t height):
    _type(type),
    _resize(resize),
    _width(width),
    _height(height)
{
}


MediaEntitySize::~MediaEntitySize()
{
}


MediaEntitySize::Type MediaEntitySize::type() const
{
    return _type;
}


MediaEntitySize::Resize MediaEntitySize::resize() const
{
    return _resize;
}


std::size_t MediaEntitySize::width() const
{
    return _width;
}


std::size_t MediaEntitySize::height() const
{
    return _height;
}


MediaEntity::MediaEntity(const std::string& url,
                         const std::string& displayURL,
                         const std::string& expandedURL,
                         const std::string& mediaURL,
                         const std::string& secureMediaURL,
                         int64_t mediaID,
                         Type type,
                         Sizes sizes,
                         int64_t sourceStatusID,
                         std::size_t startIndex,
                         std::size_t endIndex):
    URLEntity(url, displayURL, expandedURL, startIndex, endIndex),
    _mediaURL(mediaURL),
    _secureMediaURL(secureMediaURL),
    _mediaID(mediaID),
    _type(type),
    _sizes(sizes),
    _sourceStatusID(sourceStatusID)
{
}


MediaEntity::~MediaEntity()
{
}


std::string MediaEntity::mediaURL() const
{
    return _mediaURL;
}


std::string MediaEntity::secureMediaURL() const
{
    return _secureMediaURL;
}


int64_t MediaEntity::mediaID() const
{
    return _mediaID;
}


MediaEntity::Sizes MediaEntity::sizes() const
{
    return _sizes;
}


MediaEntity::Type MediaEntity::type() const
{
    return _type;
}


int64_t MediaEntity::sourceStatusID() const
{
    return _sourceStatusID;
}


UserMentionEntity::UserMentionEntity(int64_t id,
                                     const std::string& screenName,
                                     const std::string& name,
                                     std::size_t startIndex,
                                     std::size_t endIndex):
    BaseNamedUser(id, screenName, name),
    BaseIndexedEntity(startIndex, endIndex)
{
}


UserMentionEntity::~UserMentionEntity()
{
}


std::string UserMentionEntity::indexedText() const
{
    return screenName();
}


Entities::Entities()
{
}

Entities::Entities(const HashTagEntities& hashTagEntities,
                   const MediaEntities& mediaEntities,
                   const URLEntities& URLEntities,
                   const UserMentionEntities& userMentionEntities):
    _hashTagEntities(hashTagEntities),
    _mediaEntities(mediaEntities),
    _URLEntities(URLEntities),
    _userMentionEntities(userMentionEntities)
{
}


Entities::~Entities()
{
}


Entities::HashTagEntities Entities::hasTagEntities() const
{
    return _hashTagEntities;
}


Entities::MediaEntities Entities::mediaEntities() const
{
    return _mediaEntities;
}


Entities::URLEntities Entities::urlEntities() const
{
    return _URLEntities;
}


Entities::UserMentionEntities Entities::userMentionEntities() const
{
    return _userMentionEntities;
}


Entities Entities::fromJSON(const ofJson& json)
{
    Entities entities;

    auto iter = json.cbegin();
    while (iter != json.cend())
    {
        const auto& key = iter.key();
        const auto& value = iter.value();

        if (key == "hashtags")
        {
        }
        else if (key == "symbols")
        {
        }
        else if (key == "urls")
        {
        }
        else if (key == "url")
        {
        }
        else if (key == "description")
        {
        }
        else if (key == "user_mentions")
        {
        }
        else if (key == "media")
        {
// TODO: for debugging? maybe use ofxLogVerbose("ofxTwitter"), etc?
//            if (!value.is_null())
//            {
//                std::cout << key << " " << value.dump(4) << std::endl;
//            }
        }
        else ofLogWarning("Entities::fromJSON") << "Unknown key: " << key;

        ++iter;
    }

    return entities;
}



} } // namespace ofx::Twitter
