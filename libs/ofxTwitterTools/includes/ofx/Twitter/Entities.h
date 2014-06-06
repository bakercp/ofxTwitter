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


class BaseIndexedEntity
{
public:
    BaseIndexedEntity(std::size_t startIndex, std::size_t endIndex);
    virtual ~BaseIndexedEntity();

    std::size_t getStartIndex() const;
    std::size_t getEndIndex() const;

    virtual const std::string& getIndexedText() const = 0;

private:
    std::size_t _startIndex;
    std::size_t _endIndex;
    
};


class HashTagEntity: public BaseIndexedEntity
{
public:
    HashTagEntity(const std::string& hashTag,
                  std::size_t startIndex,
                  std::size_t endIndex);

    virtual ~HashTagEntity();

    const std::string& getHashTag() const;
    const std::string& getIndexedText() const;

private:
    std::string _hashTag;

};


class URLEntity: public BaseIndexedEntity
{
public:
    URLEntity(const std::string& URL,
              const std::string& URLDisplay,
              const std::string& URLExpanded,
              std::size_t startIndex,
              std::size_t endIndex);

    virtual ~URLEntity();

    const std::string& getURL() const;
    const std::string& getDisplayURL() const;
    const std::string& getExpandedURL() const;
    const std::string& getIndexedText() const;

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
                    std::size_t height);

    virtual ~MediaEntitySize();

    Type getType() const;
    Resize getResize() const;
    std::size_t getWidth() const;
    std::size_t getHeight() const;

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
                std::size_t endIndex);

    virtual ~MediaEntity();

    const std::string& getMediaURL() const;
    const std::string& getSecureMediaURL() const;
    int64_t getMediaID() const;
    Sizes getSizes() const;
    Type getType() const;
    int64_t getSourceStatusID() const;

private:
    std::string _URLMedia;
    std::string _URLMediaHTTPS;
    int64_t _mediaID;
    Sizes _sizes;
    Type _type;
    int64_t _sourceStatusID;

};


class UserMentionEntity: public BaseNamedUser, public BaseIndexedEntity
{
public:
    UserMentionEntity(int64_t ID,
                      const std::string& screenName,
                      const std::string& name,
                      std::size_t startIndex,
                      std::size_t endIndex);

    virtual ~UserMentionEntity();
    virtual const std::string& getIndexedText() const;

};


class Entities
{
public:
    typedef std::vector<HashTagEntity> HashTagEntities;
    typedef std::vector<MediaEntity> MediaEntities;
    typedef std::vector<URLEntity> URLEntities;
    typedef std::vector<UserMentionEntity> UserMentionEntities;

    Entities();

    Entities(const HashTagEntities& hashTagEntities,
             const MediaEntities& mediaEntities,
             const URLEntities& URLEntities,
             const UserMentionEntities& userMentionEntities);

    virtual ~Entities();

    const HashTagEntities& getHasTagEntities() const;
    const MediaEntities& getMediaEntities() const;
    const URLEntities& getURLEntities() const;
    const UserMentionEntities& getUserMentionEntities() const;

private:
    HashTagEntities _hashTagEntities;
    MediaEntities _mediaEntities;
    URLEntities _URLEntities;
    UserMentionEntities _userMentionEntities;

    friend class Deserializer;

};


} } // namespace ofx::Twitter
