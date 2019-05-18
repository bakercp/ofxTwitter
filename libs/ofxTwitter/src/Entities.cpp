//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/Twitter/Entities.h"
#include "ofx/Twitter/User.h"
#include "ofx/Twitter/Utils.h"
#include "ofLog.h"
#include "Poco/Exception.h"
#include "Poco/URI.h"


namespace ofx {
namespace Twitter {


BaseIndexedEntity::BaseIndexedEntity()
{
}


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


SymbolEntity::SymbolEntity()
{
}

    
SymbolEntity::SymbolEntity(std::size_t startIndex,
                           std::size_t endIndex,
                           const std::string& symbol):
    BaseIndexedEntity(startIndex, endIndex),
    _symbol(symbol)
{
}


SymbolEntity::~SymbolEntity()
{
}


std::string SymbolEntity::symbol() const
{
    return _symbol;
}


std::string SymbolEntity::indexedText() const
{
    return _symbol;
}


SymbolEntity SymbolEntity::fromJson(const ofJson& json)
{
    std::string text;
    std::size_t startIndex = 0;
    std::size_t endIndex = 0;

    auto iter = json.cbegin();
    while (iter != json.cend())
    {
        const auto& key = iter.key();
        const auto& value = iter.value();

        if (value.is_null())
        {
            ofLogError("SymbolEntity::fromJson") << "Value is NULL, key = " << key;
            ++iter;
            continue;
        }

        if (key == "indices")
        {
            if (value.size() == 2)
            {
                startIndex = value[0];
                endIndex = value[1];
            }
            else ofLogError("SymbolEntity::fromJson") << "Not two indices: " << value;
        }
        else if (key == "text") text = value;
        else ofLogWarning("SymbolEntity::fromJson") << "Unknown key: " << key;
        
        ++iter;
    }
    
    return SymbolEntity(startIndex, endIndex, text);
}



HashTagEntity::HashTagEntity(std::size_t startIndex,
                             std::size_t endIndex,
                             const std::string& hashTag):
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


HashTagEntity HashTagEntity::fromJson(const ofJson& json)
{
    std::string text;
    std::size_t startIndex = 0;
    std::size_t endIndex = 0;

    auto iter = json.cbegin();
    while (iter != json.cend())
    {
        const auto& key = iter.key();
        const auto& value = iter.value();

        if (value.is_null())
        {
            ofLogError("HashTagEntity::fromJson") << "Value is NULL, key = " << key;
            ++iter;
            continue;
        }

        if (key == "indices")
        {
            if (value.size() == 2)
            {
                startIndex = value[0];
                endIndex = value[1];
            }
            else ofLogError("HashTagEntity::fromJson") << "Not two indices: " << value;
        }
        else if (key == "text") text = value;
        else ofLogWarning("HashTagEntity::fromJson") << "Unknown key: " << key;
        
        ++iter;
    }
    
    return HashTagEntity(startIndex, endIndex, text);
}


URLEntity::URLEntity()
{
}


URLEntity::URLEntity(std::size_t startIndex,
                     std::size_t endIndex,
                     const std::string& url,
                     const std::string& displayURL,
                     const std::string& expandedURL):
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


URLEntity URLEntity::fromJson(const ofJson& json)
{
    std::size_t startIndex = 0;
    std::size_t endIndex = 0;
    std::string url;

    std::string displayUrl;
    std::string expandedUrl;

    auto iter = json.cbegin();
    while (iter != json.cend())
    {
        const auto& key = iter.key();
        const auto& value = iter.value();

        if (key == "indices")
        {
            if (value.size() == 2)
            {
                startIndex = value[0];
                endIndex = value[1];
            }
            else ofLogError("URLEntity::fromJson") << "Not two indices: " << value;
        }
        else if (key == "url") { if (!value.is_null()) url = value; }
        else if (key == "display_url") { if (!value.is_null()) displayUrl = value; }
        else if (key == "expanded_url") { if (!value.is_null()) expandedUrl = value; }
        else ofLogWarning("URLEntity::fromJson") << "Unknown key: " << key;

        ++iter;
    }

    return URLEntity(startIndex, endIndex, url, displayUrl, expandedUrl);
}


    
QuotedStatusPermalink::QuotedStatusPermalink()
{
}

    
QuotedStatusPermalink::QuotedStatusPermalink(const QuotedStatusPermalink& permalink):
    QuotedStatusPermalink(permalink.url(),
                          permalink.displayURL(),
                          permalink.expandedURL())
{
}


QuotedStatusPermalink::QuotedStatusPermalink(const std::string& url,
                                             const std::string& displayURL,
                                             const std::string& expandedURL):
    _url(url),
    _displayURL(displayURL),
    _expandedURL(expandedURL)
{
}


QuotedStatusPermalink::~QuotedStatusPermalink()
{
}


std::string QuotedStatusPermalink::url() const
{
    return _url;
}


std::string QuotedStatusPermalink::displayURL() const
{
    return _displayURL;
}


std::string QuotedStatusPermalink::expandedURL() const
{
    return _expandedURL;
}


QuotedStatusPermalink QuotedStatusPermalink::fromJson(const ofJson& json)
{
    std::string url;
    std::string displayUrl;
    std::string expandedUrl;
    
    auto iter = json.cbegin();
    while (iter != json.cend())
    {
        const auto& key = iter.key();
        const auto& value = iter.value();
        
        if (key == "url") { if (!value.is_null()) url = value; }
        else if (key == "display") { if (!value.is_null()) displayUrl = value; }
        else if (key == "expanded") { if (!value.is_null()) expandedUrl = value; }
        else ofLogWarning("QuotedStatusPermalink::fromJson") << "Unknown key: " << key;
        
        ++iter;
    }
    
    return QuotedStatusPermalink(url, displayUrl, expandedUrl);
}

    

MediaEntitySize::MediaEntitySize(Resize resize,
                                 std::size_t width,
                                 std::size_t height):
    _resize(resize),
    _width(width),
    _height(height)
{
}


MediaEntitySize::~MediaEntitySize()
{
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


MediaEntitySize MediaEntitySize::fromJson(const ofJson& json)
{
    MediaEntitySize::Resize resize = MediaEntitySize::Resize::CROP;
    std::size_t width = 0;
    std::size_t height = 0;

    auto iter = json.cbegin();
    while (iter != json.cend())
    {
        const auto& key = iter.key();
        const auto& value = iter.value();

        if (value.is_null())
        {
            ofLogError("MediaEntitySize::fromJson") << "Value is NULL, key = " << key;
            ++iter;
            continue;
        }

        if (key == "w") width = value;
        else if (key == "h") height = value;
        else if (key == "resize")
        {
            if (value == "crop") resize = MediaEntitySize::Resize::CROP;
            else if (value == "fit") resize = MediaEntitySize::Resize::FIT;
            else ofLogError("MediaEntitySize::fromJson") << "Unknown fit value: " << value;
        }
        else ofLogWarning("MediaEntitySize::fromJson") << "Unknown key: " << key;

        ++iter;
    }

    return MediaEntitySize(resize, width, height);
}


VideoInfo::VideoInfo()
{
}


VideoInfo::VideoInfo(AspectRatio aspectRatio,
                     uint64_t duration,
                     const std::vector<Variant>& variants):
    _aspectRatio(aspectRatio),
    _duration(duration),
    _variants(variants)
{
}


VideoInfo::~VideoInfo()
{
}


VideoInfo::AspectRatio VideoInfo::aspectRatio() const
{
    return _aspectRatio;
}


uint64_t VideoInfo::duration() const
{
    return _duration;
}


std::vector<VideoInfo::Variant> VideoInfo::variants() const
{
    return _variants;
}


VideoInfo VideoInfo::fromJSON(const ofJson& json)
{
    VideoInfo info;

    auto iter = json.cbegin();
    while (iter != json.cend())
    {
        const auto& key = iter.key();
        const auto& value = iter.value();

        if (value.is_null())
        {
            ofLogError("VideoInfo::fromJSON") << "Value is NULL, key = " << key;
            ++iter;
            continue;
        }


        if (key == "aspect_ratio")
        {
            if (value.size() == 2)
            {
                info._aspectRatio.x = value[0];
                info._aspectRatio.y = value[1];
            }
            else ofLogError("VideoInfo::fromJSON") << "Not two values: " << value;
        }
        else if (key == "duration_millis") info._duration = value;
        else if (key == "variants")
        {
            for (auto variant: value)
            {
                VideoInfo::Variant v;
                auto _iter = variant.cbegin();
                while (_iter != variant.cend())
                {
                    const auto& _key = _iter.key();
                    const auto& _value = _iter.value();

                    if (_key == "bitrate") v.bitrate = _value;
                    else if (_key == "content_type") v.contentType = _value;
                    else if (_key == "url") v.url = _value;
                    else ofLogError("VideoInfo::fromJSON") << "VideoInfo::Variant unknon key: " << _value;
                    ++_iter;
                }

                info._variants.push_back(v);
            }
        }
        else ofLogWarning("VideoInfo::fromJSON") << "Unknown key: " << key;

        ++iter;
    }

    return info;
}


bool AdditionalMediaInfo::monetizable() const
{
    return _montetizable;
}


std::string AdditionalMediaInfo::description() const
{
    return _description;
}
    

bool AdditionalMediaInfo::embeddable() const
{
    return _embeddable;
}


std::string AdditionalMediaInfo::title() const
{
    return _title;
}
    
    
std::shared_ptr<User> AdditionalMediaInfo::sourceUser() const
{
    return _sourceUser;
}


AdditionalMediaInfo AdditionalMediaInfo::fromJSON(const ofJson& json)
{
    AdditionalMediaInfo info;

    auto iter = json.cbegin();
    while (iter != json.cend())
    {
        const auto& key = iter.key();
        const auto& value = iter.value();

        if (Utils::endsWith(key, "_str")) { /* skip */ }
        else if (key == "monetizable")
        {
            info._montetizable = value;
        }
        else if (key == "source_user")
        {
            info._sourceUser = std::make_shared<User>(User::fromJSON(value));
        }
        else if (key == "description")
        {
            info._description = value;
        }
        else if (key == "embeddable")
        {
            info._embeddable = value;
        }
        else if (key == "title")
        {
            info._title = value;
        }
        else ofLogWarning("AdditionalMediaInfo::fromJson") << "Unknown key: " << key << " : " << value.dump(4);

        ++iter;
    }

    return info;
}



MediaEntity::MediaEntity()
{
}


MediaEntity::MediaEntity(std::size_t startIndex,
                         std::size_t endIndex,
                         const std::string& url,
                         const std::string& displayURL,
                         const std::string& expandedURL,
                         const std::string& description,
                         const std::string& mediaURL,
                         const std::string& secureMediaURL,
                         int64_t mediaID,
                         Type type,
                         const Sizes& sizes,
                         int64_t sourceStatusID,
                         int64_t sourceUserID,
                         const VideoInfo& videoInfo):
    URLEntity(startIndex, endIndex, url, displayURL, expandedURL),
    _mediaURL(mediaURL),
    _secureMediaURL(secureMediaURL),
    _description(description),
    _mediaID(mediaID),
    _type(type),
    _sizes(sizes),
    _sourceStatusID(sourceStatusID),
    _sourceUserID(sourceUserID),
    _videoInfo(videoInfo)
{
}


MediaEntity::~MediaEntity()
{
}


std::string MediaEntity::description() const
{
    return _description;
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


std::string MediaEntity::mediaFilename() const
{
    try
    {
        Poco::URI uri(mediaURL());
        std::filesystem::path path(uri.getPathEtc());
        return path.filename().string();
    }
    catch (const Poco::SyntaxException& exc)
    {
        ofLogError("MediaEntity::mediaFilename") << "Unable to parse URL " << mediaURL();
        return "";
    }
}


std::string MediaEntity::mediaFileExtension() const
{
    return std::filesystem::path(mediaFilename()).extension().string();
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


int64_t MediaEntity::sourceUserID() const
{
    return _sourceUserID;
}


VideoInfo MediaEntity::videoInfo() const
{
    return _videoInfo;
}


AdditionalMediaInfo MediaEntity::additionalMediaEntity() const
{
    return _additionalMediaInfo;
}


MediaEntity MediaEntity::fromJson(const ofJson& json)
{
    MediaEntity entity;

    auto iter = json.cbegin();
    while (iter != json.cend())
    {
        const auto& key = iter.key();
        const auto& value = iter.value();

        if (Utils::endsWith(key, "_str")) { /* skip */ }
        else if (key == "description") entity._description = value;
        else if (key == "indices")
        {
            if (value.size() == 2)
            {
                entity._startIndex = value[0];
                entity._endIndex = value[1];
            }
            else ofLogError("MediaEntity::fromJson") << "Not two indices: " << value;
        }
        else if (key == "type")
        {
            if (value == "photo") entity._type = Type::PHOTO;
            else if (value == "animated_gif") entity._type = Type::ANIMATED_GIF;
            else if (value == "video") entity._type = Type::VIDEO;
            else if (value == "multi_photo") entity._type = Type::MULTI_PHOTO;
            else ofLogError("MediaEntity::fromJson") << "Unknown type: " << value;
        }
        else if (key == "video_info") entity._videoInfo = VideoInfo::fromJSON(value);
        else if (key == "source_status_id") entity._sourceStatusID = value;
        else if (key == "source_user_id") entity._sourceUserID = value;
        else if (key == "url") entity._url = value;
        else if (key == "display_url") entity._displayURL = value;
        else if (key == "expanded_url") entity._expandedURL = value;
        else if (key == "media_url") entity._mediaURL = value;
        else if (key == "media_url_https") entity._secureMediaURL = value;
        else if (key == "sizes") entity._sizes = _sizesFromJson(value);
        else if (key == "id") entity._mediaID = value;
        else if (key == "additional_media_info") entity._additionalMediaInfo = AdditionalMediaInfo::fromJSON(value);
        else ofLogWarning("MediaEntity::fromJson") << "Unknown key: " << key << " : " << value.dump(4);

        ++iter;
    }

    return entity;
}


MediaEntity::Sizes MediaEntity::_sizesFromJson(const ofJson& json)
{
    MediaEntity::Sizes sizes;

    auto iter = json.cbegin();
    while (iter != json.cend())
    {
        const auto& key = iter.key();
        const auto& value = iter.value();

        if (key == "thumb")
        {
            auto size = MediaEntitySize::fromJson(value);
            sizes.insert(std::make_pair(MediaEntitySize::Type::THUMB, size));
        }
        else if (key == "small")
        {
            auto size = MediaEntitySize::fromJson(value);
            sizes.insert(std::make_pair(MediaEntitySize::Type::SMALL, size));
        }
        else if (key == "medium")
        {
            auto size = MediaEntitySize::fromJson(value);
            sizes.insert(std::make_pair(MediaEntitySize::Type::MEDIUM, size));
        }
        else if (key == "large")
        {
            auto size = MediaEntitySize::fromJson(value);
            sizes.insert(std::make_pair(MediaEntitySize::Type::LARGE, size));
        }
        else ofLogWarning("MediaEntity::_sizesFromJson") << "Unknown key: " << key;

        ++iter;
    }

    return sizes;
}


UserMentionEntity::UserMentionEntity()
{
}


UserMentionEntity::UserMentionEntity(std::size_t startIndex,
                                     std::size_t endIndex,
                                     int64_t id,
                                     const std::string& screenName,
                                     const std::string& name):
    BaseIndexedEntity(startIndex, endIndex),
    BaseNamedUser(id, screenName, name)
{
}


UserMentionEntity::~UserMentionEntity()
{
}


std::string UserMentionEntity::indexedText() const
{
    return screenName();
}


UserMentionEntity UserMentionEntity::fromJson(const ofJson& json)
{
    UserMentionEntity entity;

    auto iter = json.cbegin();
    while (iter != json.cend())
    {
        const auto& key = iter.key();
        const auto& value = iter.value();

        if (Utils::endsWith(key, "_str")) { /* skip */ }
        else if (key == "indices")
        {
            if (value.size() == 2)
            {
                entity._startIndex = value[0];
                entity._endIndex = value[1];
            }
            else ofLogError("URLEntity::fromJson") << "Not two indices: " << value;
        }
        else if (key == "id") entity._id = value;
        else if (key == "name") entity._name = value;
        else if (key == "screen_name") entity._screenName = value;
        else ofLogWarning("UserMentionEntity::fromJson") << "Unknown key: " << key;

        ++iter;
    }

    return entity;
}


Entities::Entities()
{
}


Entities::Entities(const HashTagEntities& hashTagEntities,
                   const SymbolEntities& symbolEntities,
                   const MediaEntities& mediaEntities,
                   const URLEntities& URLEntities,
                   const UserMentionEntities& userMentionEntities):
    _hashTagEntities(hashTagEntities),
    _symbolEntities(symbolEntities),
    _mediaEntities(mediaEntities),
    _URLEntities(URLEntities),
    _userMentionEntities(userMentionEntities)
{
}


Entities::~Entities()
{
}


Entities::HashTagEntities Entities::hashTagEntities() const
{
    return _hashTagEntities;
}


Entities::SymbolEntities Entities::symbolEntities() const
{
    return _symbolEntities;
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
            for (auto hashtag: value)
            {
                auto entity = HashTagEntity::fromJson(hashtag);
                entities._hashTagEntities.push_back(entity);
            }
        }
        else if (key == "symbols")
        {
            for (auto hashtag: value)
            {
                auto entity = SymbolEntity::fromJson(hashtag);
                entities._symbolEntities.push_back(entity);
            }
        }
        else if (key == "urls")
        {
            for (auto url: value)
            {
                auto entity = URLEntity::fromJson(url);

                if (!entity.url().empty())
                {
                    entities._URLEntities.push_back(entity);
                }
            }
        }
        else if (key == "url" || key == "description")
        {
            for (auto url: value["urls"])
            {
                auto entity = URLEntity::fromJson(url);

                if (!entity.url().empty())
                {
                    entities._URLEntities.push_back(entity);
                }
            }
        }
        else if (key == "user_mentions")
        {
            for (auto user: value)
            {
                auto entity = UserMentionEntity::fromJson(user);
                entities._userMentionEntities.push_back(entity);
            }
        }
        else if (key == "media")
        {
            for (auto media: value)
            {
                auto entity = MediaEntity::fromJson(media);
                entities._mediaEntities.push_back(entity);
            }
        }
        else ofLogWarning("Entities::fromJSON") << "Unknown key: " << key;

        ++iter;
    }

    return entities;
}



} } // namespace ofx::Twitter
