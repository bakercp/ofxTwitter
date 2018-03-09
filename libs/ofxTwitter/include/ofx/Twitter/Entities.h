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


class User;


/// \brief The base class for an indexed entity.
class BaseIndexedEntity
{
public:
    /// \brief Create an indexed entity.
    BaseIndexedEntity();

    /// \brief Create an indexed entity.
    /// \param startIndex The start index of the indexed entity in the Status text.
    /// \param endIndex The end index of the indexed entity in the Status text.
    BaseIndexedEntity(std::size_t startIndex, std::size_t endIndex);

    /// \brief Destroy the BaseIndexedEntity.
    virtual ~BaseIndexedEntity();

    /// \returns The start index of the indexed entity in the Status text.
    std::size_t startIndex() const;

    /// \returns The end index of the indexed entity in the Status text.
    std::size_t endIndex() const;

    /// \returns the text indexed by the start and end indices.
    virtual std::string indexedText() const = 0;

protected:
    /// \brief The start index of the indexed entity in the Status text.
    std::size_t _startIndex = 0;

    /// \brief The end index of the indexed entity in the Status text.
    std::size_t _endIndex = 0;

};


/// \brief A Symbol indexed entity.
/// \sa https://dev.twitter.com/overview/api/entities-in-twitter-objects#symbols
class SymbolEntity: public BaseIndexedEntity
{
public:
    /// \brief Create an empty Symbol entity.
    SymbolEntity();

    /// \brief Create an Symbol entity.
    /// \param startIndex The start index of the indexed entity in the Status text.
    /// \param endIndex The end index of the indexed entity in the Status text.
    /// \param symbol The Symbol represented by this entity.
    SymbolEntity(std::size_t startIndex,
                  std::size_t endIndex,
                  const std::string& symbol);

    /// \brief Destroy the SymbolEntity.
    virtual ~SymbolEntity();

    /// \returns the symbol text.
    std::string symbol() const;

    std::string indexedText() const override;

    /// \brief Extract the SymbolEntity from JSON.
    /// \param json The source JSON.
    /// \returns the extracted SymbolEntity.
    static SymbolEntity fromJson(const ofJson& json);

private:
    /// \brief The Symbol text.
    std::string _symbol;

};


/// \brief A Hashtag indexed entity.
/// \sa https://dev.twitter.com/overview/api/entities-in-twitter-objects#hashtags
class HashTagEntity: public BaseIndexedEntity
{
public:
    /// \brief Create an indexed entity.
    /// \param startIndex The start index of the indexed entity in the Status text.
    /// \param endIndex The end index of the indexed entity in the Status text.
    /// \param hashTag The hashtag represented by this entity.
    HashTagEntity(std::size_t startIndex,
                  std::size_t endIndex,
                  const std::string& hashTag);

    /// \brief Destroy the HashTagEntity.
    virtual ~HashTagEntity();

    /// \returns the hashtag text.
    std::string hashTag() const;

    std::string indexedText() const override;

    /// \brief Extract the HashTagEntity from JSON.
    /// \param json The source JSON.
    /// \returns the extracted HashTagEntity.
    static HashTagEntity fromJson(const ofJson& json);

private:
    /// \brief The hashtag text.
    std::string _hashTag;

};


/// \brief An URL entity.
/// \sa https://dev.twitter.com/overview/api/entities-in-twitter-objects#urls
class URLEntity: public BaseIndexedEntity
{
public:
    /// \brief Construct an empty URLEntity.
    URLEntity();

    /// \brief Construct an URLEntity.
    /// \param startIndex The start index of the indexed entity in the Status text.
    /// \param endIndex The end index of the indexed entity in the Status text.
    /// \param url The URL that was extracted.
    /// \param displayURL Not a URL but a string to display instead of the URL.
    /// \param expandedURL The fully resolved URL.
    URLEntity(std::size_t startIndex,
              std::size_t endIndex,
              const std::string& url,
              const std::string& displayURL,
              const std::string& expandedURL);

    /// \brief Destroy the URL entity.
    virtual ~URLEntity();

    /// \returns the URL that was extracted.
    std::string url() const;

    /// \returns the displayable URL.
    std::string displayURL() const;

    /// \returns The fully resolved URL.
    std::string expandedURL() const;

    std::string indexedText() const override;

    /// \brief Extract the URLEntity from JSON.
    /// \param json The source JSON.
    /// \returns the extracted URLEntity.
    static URLEntity fromJson(const ofJson& json);

protected:
    /// \brief The URL that was extracted.
    std::string _url;

    /// \brief The displayable URL string.
    std::string _displayURL;

    /// \brief The fully resolved URL.
    std::string _expandedURL;

};


/// \brief A Media Entity Size entry.
///
/// We support different sizes: thumb, small, medium and large. The media_url
/// defaults to medium but you can retrieve the media in different sizes by
/// appending a colon + the size key (for example:
/// http://pbs.twimg.com/media/A7EiDWcCYAAZT1D.jpg:thumb ). Each available size
/// comes with three attributes that describe it: w : the width (in pixels) of
/// the media in this particular size; h : the height (in pixels) of the media
/// in this particular size; and resize : how we resized the media to this
/// particular size (can be crop or fit ).
class MediaEntitySize
{
public:
    /// \brief Media Entity Size types.
    ///
    /// This indicates the size by name.
    enum class Type
    {
        /// \brief A thumbnail size.
        THUMB,
        /// \brief A small size.
        SMALL,
        /// \brief A medium size.
        MEDIUM,
        /// \brief A large size.
        LARGE
    };

    /// \brief Media Entity Size resize types.
    ///
    /// This indicates how the media was resized.
    enum class Resize
    {
        /// \brief The image was cropped to attain this size.
        CROP,
        /// \brief The image fit in this resized size.
        FIT
    };

    /// \brief Create a MediaEntitySize.
    /// \param resize The resize type for this size.
    /// \param width The width of this size.
    /// \param height The height of this size.
    MediaEntitySize(Resize resize,
                    std::size_t width,
                    std::size_t height);

    /// \brief Destroy the MediaEntitySize.
    virtual ~MediaEntitySize();

    /// \returns the resize type for this size.
    Resize resize() const;

    /// \returns the width of this size.
    std::size_t width() const;

    /// \returns the height of this size.
    std::size_t height() const;

    /// \brief Extract the MediaEntitySize from JSON.
    /// \param json The source JSON.
    /// \returns the extracted MediaEntitySize.
    static MediaEntitySize fromJson(const ofJson& json);

private:
    /// \brief The method used to attain this size, if resized.
    Resize _resize = Resize::CROP;

    /// \brief The width of this size.
    std::size_t _width = 0;

    /// \brief The height of this size.
    std::size_t _height = 0;

};


/// \brief Information present when a
class VideoInfo
{
public:
    /// \brief The aspect ratio X / Y of the video.
    struct AspectRatio
    {
        std::size_t x = 0;
        std::size_t y = 0;
    };

    /// \brief A structure representing a variation on the video.
    struct Variant
    {
        /// \brief The video bitrate.
        uint64_t bitrate = 0;

        /// \brief The video's content (MIME) type.
        std::string contentType;

        /// \brief The URL of the variant.
        std::string url;
    };

    /// \brief Create an empty VideoInfo.
    VideoInfo();

    /// \brief Create a VideoInfo with the given parameters.
    /// \param aspectRatio The aspect ratio of the video.
    /// \param duration The duration of the video in milliseconds.
    /// \param variants A collection of variants of this video.
    VideoInfo(AspectRatio aspectRatio,
              uint64_t duration,
              const std::vector<Variant>& variants);

    /// \brief Destory the VideoInfo.
    virtual ~VideoInfo();

    /// \returns the AspectRatio of the video.
    AspectRatio aspectRatio() const;

    /// \returns the length of the video, in milliseconds.
    uint64_t duration() const;

    /// \returns the variants of the video.
    std::vector<Variant> variants() const;

    /// \brief Extract the VideoInfo from JSON.
    /// \param json The source JSON.
    /// \returns the extracted VideoInfo.
    static VideoInfo fromJSON(const ofJson& json);

private:
    /// \brief The AspectRatio of the video.
    AspectRatio _aspectRatio;

    /// \brief The length of the video, in milliseconds.
    uint64_t _duration = 0;

    /// \brief The variants of the video.
    std::vector<Variant> _variants;

};


class AdditionalMediaInfo
{
public:
    /// \returns true if monetizable.
    bool monetizable() const;

    /// \returns a shared pointer to a source user if available.
    std::shared_ptr<User> sourceUser() const;

    /// \brief Extract the VideoInfo from JSON.
    /// \param json The source JSON.
    /// \returns the extracted VideoInfo.
    static AdditionalMediaInfo fromJSON(const ofJson& json);

private:
    bool _montetizable = false;

    std::shared_ptr<User> _sourceUser;

};


/// \brief An entity containing media.
/// \sa https://dev.twitter.com/overview/api/entities-in-twitter-objects#media
class MediaEntity: public URLEntity
{
public:
    /// \brief A typedef for Sizes.
    typedef std::map<MediaEntitySize::Type, MediaEntitySize> Sizes;

    /// \brief MediaEntity types.
    enum class Type
    {
        /// \brief The MediaEntity is a photo.
        PHOTO,

        /// \brief The MediaEntity is multiple photos.
        MULTI_PHOTO,

        /// \brief The MediaEntity is an animated GIF.
        ANIMATED_GIF,

        /// \brief The MediaEntity is a video.
        VIDEO
    };

    /// \brief Convert a Type to std::string.
    /// \param type The type to convert.
    /// \returns the string representation of the given Type.
    static std::string to_string(Type type)
    {
        switch (type)
        {
            case Type::PHOTO: return "photo";
            case Type::MULTI_PHOTO: return "multi_photo";
            case Type::ANIMATED_GIF: return "animated_gif";
            case Type::VIDEO: return "video";
        }
    }

    /// \brief Construct an empty MediaEntity.
    MediaEntity();

    /// \brief Construct a MediaEntity.
    /// \param startIndex The start index of the indexed entity in the Status text.
    /// \param endIndex The end index of the indexed entity in the Status text.
    /// \param url The URL that was extracted.
    /// \param displayURL Not a URL but a string to display instead of the URL.
    /// \param expandedURL The fully resolved URL.
    /// \param mediaURL The media URL.
    /// \param secureMediaURL the SSL URL of the media file.
    /// \param mediaID The media ID.
    /// \param The media type.
    /// \param The available media sizes.
    /// \param sourceStatusID The source Status ID for this media.
    /// \param sourceUserID The source User ID for this media.
    MediaEntity(std::size_t startIndex,
                std::size_t endIndex,
                const std::string& url,
                const std::string& displayURL,
                const std::string& expandedURL,
                const std::string& mediaURL,
                const std::string& secureMediaURL,
                int64_t mediaID,
                Type type,
                const Sizes& sizes,
                int64_t sourceStatusID,
                int64_t sourceUserID,
                const VideoInfo& videoInfo);

    /// \brief Destroy the MediaEntity.
    virtual ~MediaEntity();

    /// \returns the URL of the media file.
    std::string mediaURL() const;

    /// \returns the SSL URL of the media file.
    std::string secureMediaURL() const;

    /// \returns the media ID.
    int64_t mediaID() const;

    /// \returns the filename if available.
    std::string mediaFilename() const;

    /// \returns the media file extension, if available.
    std::string mediaFileExtension() const;

    /// \returns the available sizes.
    Sizes sizes() const;

    /// \returns the media type.
    Type type() const;

    /// \returns the source Status ID for this media.
    int64_t sourceStatusID() const;

    /// \returns the source User ID for this media.
    int64_t sourceUserID() const;

    /// \returns the video info if the media type is a video.
    VideoInfo videoInfo() const;

    /// \returns the AdditionalMediaInfo if available.
    AdditionalMediaInfo additionalMediaEntity() const;

    /// \brief Extract the MediaEntity from JSON.
    /// \param json The source JSON.
    /// \returns the extracted MediaEntity.
    static MediaEntity fromJson(const ofJson& json);

private:
    static Sizes _sizesFromJson(const ofJson& json);

    /// \brief The URL of the media file.
    std::string _mediaURL;

    /// \brief The SSL URL of the media file.
    std::string _secureMediaURL;

    /// \brief The media ID.
    int64_t _mediaID = -1;

    /// \brief The media type.
    Type _type = Type::PHOTO;

    /// \brief The available sizes.
    Sizes _sizes;

    /// \brief The source Status ID for this media.
    int64_t _sourceStatusID = -1;

    /// \brief The source User ID for this media.
    int64_t _sourceUserID = -1;

    /// \brief Video info for this media, if available.
    VideoInfo _videoInfo;

    /// \brief Additional media info, if available.
    AdditionalMediaInfo _additionalMediaInfo;

};


/// \brief A user mention entity.
/// \sa https://dev.twitter.com/overview/api/entities-in-twitter-objects#user_mentions
class UserMentionEntity: public BaseNamedUser, public BaseIndexedEntity
{
public:
    /// \brief Create a default UserMentionEntity.
    UserMentionEntity();

    /// \param startIndex The start index of the indexed entity in the Status text.
    /// \param endIndex The end index of the indexed entity in the Status text.
    UserMentionEntity(std::size_t startIndex,
                      std::size_t endIndex,
                      int64_t id,
                      const std::string& screenName,
                      const std::string& name);

    /// \brief Destory the UserMentionEntity.
    virtual ~UserMentionEntity();

    virtual std::string indexedText() const override;

    /// \brief Extract the UserMentionEntity from JSON.
    /// \param json The source JSON.
    /// \returns the extracted UserMentionEntity.
    static UserMentionEntity fromJson(const ofJson& json);

};


class Entities
{
public:
    typedef std::vector<HashTagEntity> HashTagEntities;
    typedef std::vector<SymbolEntity> SymbolEntities;
    typedef std::vector<MediaEntity> MediaEntities;
    typedef std::vector<URLEntity> URLEntities;
    typedef std::vector<UserMentionEntity> UserMentionEntities;

    Entities();

    Entities(const HashTagEntities& hashTagEntities,
             const SymbolEntities& symbolEntities,
             const MediaEntities& mediaEntities,
             const URLEntities& URLEntities,
             const UserMentionEntities& userMentionEntities);

    virtual ~Entities();

    HashTagEntities hashTagEntities() const;
    SymbolEntities symbolEntities() const;
    MediaEntities mediaEntities() const;
    URLEntities urlEntities() const;
    UserMentionEntities userMentionEntities() const;

    /// \brief Extract the Entities from JSON.
    /// \param json The source JSON.
    /// \returns the extracted Entities.
    static Entities fromJSON(const ofJson& json);

private:
    HashTagEntities _hashTagEntities;
    SymbolEntities _symbolEntities;
    MediaEntities _mediaEntities;
    URLEntities _URLEntities;
    UserMentionEntities _userMentionEntities;

};


} } // namespace ofx::Twitter
