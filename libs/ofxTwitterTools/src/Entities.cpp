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


std::size_t BaseIndexedEntity::getStartIndex() const
{
    return _startIndex;
}


std::size_t BaseIndexedEntity::getEndIndex() const
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


const std::string& HashTagEntity::getHashTag() const
{
    return _hashTag;
}


const std::string& HashTagEntity::getIndexedText() const
{
    return _hashTag;
}


URLEntity::URLEntity(const std::string& URL,
                     const std::string& URLDisplay,
                     const std::string& URLExpanded,
                     std::size_t startIndex,
                     std::size_t endIndex):
    _URL(URL),
    _URLDisplay(URLDisplay),
    _URLExpanded(URLExpanded),
    BaseIndexedEntity(startIndex, endIndex)
{
}


URLEntity::~URLEntity()
{
}


const std::string& URLEntity::getURL() const
{
    return _URL;
}


const std::string& URLEntity::getDisplayURL() const
{
    return _URLDisplay;
}


const std::string& URLEntity::getExpandedURL() const
{
    return _URLExpanded;
}


const std::string& URLEntity::getIndexedText() const
{
    return _URL;
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


MediaEntitySize::Type MediaEntitySize::getType() const
{
    return _type;
}


MediaEntitySize::Resize MediaEntitySize::getResize() const
{
    return _resize;
}


std::size_t MediaEntitySize::getWidth() const
{
    return _width;
}


std::size_t MediaEntitySize::getHeight() const
{
    return _height;
}


MediaEntity::MediaEntity(const std::string& URL,
                         const std::string& URLDisplay,
                         const std::string& URLExpanded,
                         const std::string& URLMedia,
                         const std::string& URLMediaHTTPS,
                         int64_t mediaID,
                         Type type,
                         Sizes sizes,
                         int64_t sourceStatusID,
                         std::size_t startIndex,
                         std::size_t endIndex):
    URLEntity(URL, URLDisplay, URLExpanded, startIndex, endIndex),
    _URLMedia(URLMedia),
    _URLMediaHTTPS(URLMediaHTTPS),
    _mediaID(mediaID),
    _type(type),
    _sizes(sizes),
    _sourceStatusID(sourceStatusID)
{
}


MediaEntity::~MediaEntity()
{
}


const std::string& MediaEntity::getMediaURL() const
{
    return _URLMedia;
}


const std::string& MediaEntity::getSecureMediaURL() const
{
    return _URLMediaHTTPS;
}


int64_t MediaEntity::getMediaID() const
{
    return _mediaID;
}


MediaEntity::Sizes MediaEntity::getSizes() const
{
    return _sizes;
}


MediaEntity::Type MediaEntity::getType() const
{
    return _type;
}


int64_t MediaEntity::getSourceStatusID() const
{
    return _sourceStatusID;
}


UserMentionEntity::UserMentionEntity(int64_t ID,
                                     const std::string& screenName,
                                     const std::string& name,
                                     std::size_t startIndex,
                                     std::size_t endIndex):
    BaseNamedUser(ID, screenName, name),
    BaseIndexedEntity(startIndex, endIndex)
{
}


UserMentionEntity::~UserMentionEntity()
{
}


const std::string& UserMentionEntity::getIndexedText() const
{
    return getScreenName();
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

    
const Entities::HashTagEntities& Entities::getHasTagEntities() const
{
    return _hashTagEntities;
}


const Entities::MediaEntities& Entities::getMediaEntities() const
{
    return _mediaEntities;
}


const Entities::URLEntities& Entities::getURLEntities() const
{
    return _URLEntities;
}


const Entities::UserMentionEntities& Entities::getUserMentionEntities() const
{
    return _userMentionEntities;
}


} } // namespace ofx::Twitter
