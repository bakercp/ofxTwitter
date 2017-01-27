//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include <string>
#include <vector>
#include <map>
#include "json.hpp"
#include "ofx/Twitter/BaseUser.h"


namespace ofx {
namespace Twitter {


class BaseIndexedEntity
{
public:
    BaseIndexedEntity(std::size_t startIndex, std::size_t endIndex);

    virtual ~BaseIndexedEntity();

    std::size_t startIndex() const;
    std::size_t endIndex() const;

    virtual std::string indexedText() const = 0;

private:
    /// \brief The start index of the indexed entity in the Status text.
    std::size_t _startIndex = 0;

    /// \brief The end index of the indexed entity in the Status text.
    std::size_t _endIndex = 0;

};


class HashTagEntity: public BaseIndexedEntity
{
public:
    HashTagEntity(const std::string& hashTag,
                  std::size_t startIndex,
                  std::size_t endIndex);

    virtual ~HashTagEntity();

    std::string hashTag() const;
    std::string indexedText() const override;

private:
    /// \brief The hashtag text.
    std::string _hashTag;

};


class URLEntity: public BaseIndexedEntity
{
public:
    URLEntity(const std::string& url,
              const std::string& displayURL,
              const std::string& expandedURL,
              std::size_t startIndex,
              std::size_t endIndex);

    virtual ~URLEntity();

    std::string url() const;
    std::string displayURL() const;
    std::string expandedURL() const;
    std::string indexedText() const;

private:
    std::string _url;
    std::string _displayURL;
    std::string _expandedURL;

};


class MediaEntitySize
{
public:
    enum class Type
    {
        THUMB,
        SMALL,
        MEDIUM,
        LARGE
    };

    enum class Resize
    {
        CROP,
        FIT
    };

    MediaEntitySize(Type type,
                    Resize resize,
                    std::size_t width,
                    std::size_t height);

    virtual ~MediaEntitySize();

    Type type() const;
    Resize resize() const;
    std::size_t width() const;
    std::size_t height() const;

private:
    Type _type = Type::THUMB;
    Resize _resize = Resize::CROP;
    std::size_t _width = 0;
    std::size_t _height = 0;

};


class MediaEntity: public URLEntity
{
public:
    typedef std::map<MediaEntitySize::Type, MediaEntitySize> Sizes;

    enum class Type
    {
        PHOTO
    };

    MediaEntity(const std::string& url,
                const std::string& displayURL,
                const std::string& expandedURL,
                const std::string& mediaURL,
                const std::string& secureMediaURL,
                int64_t mediaID,
                Type type,
                Sizes sizes,
                int64_t sourceStatusID,
                std::size_t startIndex,
                std::size_t endIndex);

    virtual ~MediaEntity();

    std::string mediaURL() const;
    std::string secureMediaURL() const;
    int64_t mediaID() const;
    Sizes sizes() const;
    Type type() const;
    int64_t sourceStatusID() const;

private:
    std::string _mediaURL;
    std::string _secureMediaURL;
    int64_t _mediaID = 0;
    Type _type = Type::PHOTO;
    Sizes _sizes;
    int64_t _sourceStatusID = -1;

};


class UserMentionEntity: public BaseNamedUser, public BaseIndexedEntity
{
public:
    UserMentionEntity(int64_t id,
                      const std::string& screenName,
                      const std::string& name,
                      std::size_t startIndex,
                      std::size_t endIndex);

    virtual ~UserMentionEntity();

    virtual std::string indexedText() const override;

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

    HashTagEntities hasTagEntities() const;
    MediaEntities mediaEntities() const;
    URLEntities urlEntities() const;
    UserMentionEntities userMentionEntities() const;

    static Entities fromJSON(const ofJson& json);

private:
    HashTagEntities _hashTagEntities;
    MediaEntities _mediaEntities;
    URLEntities _URLEntities;
    UserMentionEntities _userMentionEntities;

};


} } // namespace ofx::Twitter
