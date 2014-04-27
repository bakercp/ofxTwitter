// =============================================================================
//
// Copyright (c) 2009-2013 Christopher Baker <http://christopherbaker.net>
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


#include <string>
#include <vector>
#include <map>
#include "ofx/Twitter/Types.h"


namespace ofx {
namespace Twitter {


class AbstractIndexedEntity
{
public:
    AbstractIndexedEntity(std::size_t startIndex, std::size_t endIndex):
        _startIndex(startIndex),
        _endIndex(endIndex)
    {
    }


    virtual ~AbstractIndexedEntity()
    {
    }


    std::size_t getStartIndex() const
    {
        return _startIndex;
    }


    std::size_t getEndIndex() const
    {
        return _endIndex;
    }


    virtual std::string getIndexedText() const = 0;

private:
    std::size_t _startIndex;
    std::size_t _endIndex;

};


class HashTagEntity: public AbstractIndexedEntity
{
public:
    HashTagEntity(const std::string& hashTag,
                  std::size_t startIndex,
                  std::size_t endIndex):
        AbstractIndexedEntity(startIndex, endIndex),
        _hashTag(hashTag)
    {
    }

    virtual ~HashTagEntity()
    {
    }

    std::string getHashTag() const
    {
        return _hashTag;
    }

    std::string getIndexedText() const
    {
        return _hashTag;
    }

private:
    std::string _hashTag;

};


class URLEntity: public AbstractIndexedEntity
{
public:
    URLEntity(const std::string& URL,
              const std::string& URLDisplay,
              const std::string& URLExpanded,
              std::size_t startIndex,
              std::size_t endIndex):
        _URL(URL),
        _URLDisplay(URLDisplay),
        _URLExpanded(URLExpanded),
        AbstractIndexedEntity(startIndex, endIndex)
    {
    }

    virtual ~URLEntity()
    {
    }

    std::string getURL() const
    {
        return _URL;
    }

    std::string getDisplayURL() const
    {
        return _URLDisplay;
    }

    std::string getExpandedURL() const
    {
        return _URLExpanded;
    }

    std::string getIndexedText() const
    {
      return _URL;
    }

private:
    std::string _URL;
    std::string _URLDisplay;
    std::string _URLExpanded;

};


class MediaEntitySize
{
public:
    enum Type
    {
        THUMB,
        SMALL,
        MEDIUM,
        LARGE
    };

    enum Resize
    {
        CROP,
        FIT
    };

    MediaEntitySize(Type type,
                    Resize resize,
                    std::size_t width,
                    std::size_t height):
        _type(type),
        _resize(resize),
        _width(width),
        _height(height)
    {
    }


    virtual ~MediaEntitySize()
    {
    }


    Type getType() const
    {
        return _type;
    }


    Resize getResize() const
    {
        return _resize;
    }


    std::size_t getWidth() const
    {
        return _width;
    }


    std::size_t getHeight() const
    {
        return _height;
    }


private:
    Type _type;
    Resize _resize;
    std::size_t _width;
    std::size_t _height;

};


class MediaEntity: public URLEntity
{
public:
    typedef std::map<MediaEntitySize::Type, MediaEntitySize> Sizes;

    enum Type
    {
        PHOTO
    };

    MediaEntity(const std::string& URL,
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

    virtual ~MediaEntity()
    {
    }

    std::string getMediaURL() const
    {
        return _URLMedia;
    }

    std::string getSecureMediaURL() const
    {
        return _URLMediaHTTPS;
    }

    int64_t getMediaID() const
    {
        return _mediaID;
    }

    Sizes GetSizes() const
    {
        return _sizes;
    }

    Type getType() const
    {
        return _type;
    }

    int64_t getSourceStatusID() const
    {
        return _sourceStatusID;
    }

private:
    std::string _URLMedia;
    std::string _URLMediaHTTPS;
    int64_t _mediaID;
    Sizes _sizes;
    Type _type;
    int64_t _sourceStatusID;


};


class UserMentionEntity:
    public BaseNamedUser,
    public AbstractIndexedEntity
{
public:
    UserMentionEntity(int64_t ID,
                      const std::string& screenName,
                      const std::string& name,
                      std::size_t startIndex,
                      std::size_t endIndex):
        BaseNamedUser(ID, screenName, name),
        AbstractIndexedEntity(startIndex, endIndex)
    {
    }

    virtual ~UserMentionEntity()
    {
    }

    virtual std::string getIndexedText() const
    {
        return getScreenName();
    }

};



class Entities
{
public:
    typedef std::vector<HashTagEntity> HashTagEntities;
    typedef std::vector<MediaEntity> MediaEntities;
    typedef std::vector<URLEntity> URLEntities;
    typedef std::vector<UserMentionEntity> UserMentionEntities;


    Entities()
    {
    }

    Entities(const HashTagEntities& hashTagEntities,
             const MediaEntities& mediaEntities,
             const URLEntities& URLEntities,
             const UserMentionEntities& userMentionEntities):
        _hashTagEntities(hashTagEntities),
        _mediaEntities(mediaEntities),
        _URLEntities(URLEntities),
        _userMentionEntities(userMentionEntities)
    {
    }

    ~Entities()
    {
    }

    HashTagEntities getHasTagEntities() const
    {
        return _hashTagEntities;
    }

    MediaEntities getMediaEntities() const
    {
        return _mediaEntities;
    }

    URLEntities getURLEntities() const
    {
        return _URLEntities;
    }

    UserMentionEntities getUserMentionEntities() const
    {
        return _userMentionEntities;
    }

private:
    HashTagEntities _hashTagEntities;
    MediaEntities _mediaEntities;
    URLEntities _URLEntities;
    UserMentionEntities _userMentionEntities;

    friend class Deserializer;

};


} } // namespace ofx::Twitter
