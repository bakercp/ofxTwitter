// =============================================================================
//
// Copyright (c) 2009-2015 Christopher Baker <http://christopherbaker.net>
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


#include <stdint.h>
#include "ofx/TaskQueue.h"
#include "ofx/TaskQueueEvents.h"
#include "ofx/Geo/CoordinateBounds.h"
#include "ofx/Twitter/Tweet.h"
#include "ofx/Twitter/Deserializer.h"
#include "ofx/Twitter/Credentials.h"


namespace ofx {
namespace Twitter {


//typedef TaskDataEventArgs_<Poco::UUID, ClientResponseBufferEventArgs> ClientBufferEventArgs;

class StreamingParameters: public Poco::Net::NameValueCollection
{
public:
    enum FilterLevel
    {
        NONE,
        LOW,
        MEDIUM
    };

    StreamingParameters();

    virtual ~StreamingParameters();

    /// \sa https://dev.twitter.com/streaming/overview/request-parameters#delimited
    void setDelimited(const std::string& delimited = DEFAULT_DELIMITED);

    /// \brief The Tweet filter level.
    /// \sa https://dev.twitter.com/streaming/overview/request-parameters#track
    void setFilterLevel(FilterLevel filterLevel);

    /// \brief A comma delimited list of languages to track.
    /// \sa https://dev.twitter.com/streaming/overview/request-parameters#language
    /// \sa http://tools.ietf.org/html/bcp47
    void setLanguages(const std::string& language);

    static const std::string DEFAULT_DELIMITED;

    FilterLevel _filterLevel;

    /// \brief Elevated access clients use count to backfill missed messages.
    /// \sa https://dev.twitter.com/streaming/overview/request-parameters#count
    int _count;

    std::string _with;

};


class FilterQuery: public StreamingParameters
{
public:
    FilterQuery();
    virtual ~FilterQuery();


    /// \brief A list of phrases to track.
    /// \sa https://dev.twitter.com/streaming/overview/request-parameters#track
    std::vector<std::string> _track;

    /// \brief A list of users to track.
    /// \sa https://dev.twitter.com/streaming/overview/request-parameters#follow
    std::vector<std::string> _follow;

};



//    typedef TaskDataEventArgs_<std::string, ClientResponseBufferEventArgs> ClientBufferEventArgs;



class StreamingClient
{
public:
    enum StreamType
    {
        FILTER,
        SAMPLE,
        FIREHOSE,
    };

    StreamingClient(int maxTasks = TaskQueue::UNLIMITED_TASKS,
                    Poco::ThreadPool& threadPool = Poco::ThreadPool::defaultPool());

    virtual ~StreamingClient();

    Poco::UUID sample();

    Poco::UUID filter(std::vector<std::string> follow,
                      std::vector<std::string> track,
                      std::vector<Geo::CoordinateBounds> locations);

    enum WithParam
    {
        USERS,
        FOLLOWINGS
    };

    enum Replies
    {
        ALL
    };

    std::string user(WithParam with,
                    Replies replies,
                    std::vector<std::string> follow,
                    std::vector<std::string> track,
                    std::vector<Geo::CoordinateBounds> locations);
                    // stringify_friend_ids=false


    /// https://sitestream.twitter.com/1.1/site.json
    /// https://dev.twitter.com/streaming/sitestreams
    std::string site(WithParam with,
                    Replies replies,
                    std::vector<std::string> follow);
                    // stringify_friend_ids=false
                    // delimited=length
                    // stall_warnings=true

    /// https://stream.twitter.com/1.1/statuses/firehose.json
    std::string firehose(int count);
    // delimited=length
    // stall_warnings=true


    void setCredentials(const Credentials& credentials);

    const Credentials& getCredentials() const;


////    Poco::UUID get(const std::string& uri,
////                   const Poco::Net::NameValueCollection& formFields = Poco::Net::NameValueCollection(),
////                   const std::string& httpVersion = Poco::Net::HTTPMessage::HTTP_1_1,
////                   const Poco::UUID& requestId = BaseRequest::generateUUID(),
////                   ThreadSettings threadSettings = ThreadSettings());
//
//    /// \brief Construct a PostRequest with a given uri and http version.
//    /// \param uri the Post endpoint uri.
//    /// \param formFields A collection of form fields.
//    /// \param formParts A collection of form parts.
//    /// \param httpVersion Either HTTP/1.0 or HTTP/1.1.
//    /// \param requestId A unique UUID for this request.
//    /// \returns a UUID associated with the BaseRequest.
//    Poco::UUID post(const std::string& uri,
//                    const Poco::Net::NameValueCollection formFields = Poco::Net::NameValueCollection(),
//                    const PostRequest::FormParts formParts = PostRequest::FormParts(),
//                    const std::string& httpVersion = Poco::Net::HTTPMessage::HTTP_1_1,
//                    const Poco::UUID& requestId = BaseRequest::generateUUID(),
//                    ThreadSettings threadSettings = ThreadSettings());
//
//    /// \brief Submit a request.
//    ///
//    /// The DefaultClientPool will take ownership of the pointer and destroy
//    /// it after use.  Users must not attempt to modify the request after it
//    /// has been submitted.
//    ///
//    /// \returns a UUID associated with the BaseRequest.
//    Poco::UUID request(BaseRequest* pRequest,
//                       ThreadSettings threadSettings = ThreadSettings());

//    /// \brief Register event listeners.
//    /// \tparam ListenerClass The class type with the required callback methods.
//    /// \param listener a pointer to the listening class (usually "this").
//    template<class ListenerClass>
//    void registerAllEvents(ListenerClass* listener);
//
//    /// \brief Unregister event listeners.
//    /// \tparam ListenerClass The class type with the required callback methods.
//    /// \param listener a pointer to the listening class (usually "this").
//    template<class ListenerClass>
//    void unregisterAllEvents(ListenerClass* listener);

//    ofEvent<const ClientBufferEventArgs> onTweet;

private:
//    DefaultClientTaskQueue(const DefaultClientTaskQueue&);
//    DefaultClientTaskQueue& operator = (const DefaultClientTaskQueue&);
//
//    virtual void handleTaskCustomNotification(const Poco::UUID& taskID,
//                                              Poco::AutoPtr<Poco::TaskNotification> pNotification);

    Credentials _credentials;

};


//template<typename ListenerClass>
//void DefaultClientTaskQueue::registerAllEvents(ListenerClass* listener)
//{
//    TaskQueue_<Poco::UUID>::registerTaskProgressEvents(listener);
//    ofAddListener(onClientBuffer, listener, &ListenerClass::onClientBuffer);
//}
//
//
//template<typename ListenerClass>
//void DefaultClientTaskQueue::unregisterAllEvents(ListenerClass* listener)
//{
//    TaskQueue_<Poco::UUID>::unregisterTaskProgressEvents(listener);
//    ofRemoveListener(onClientBuffer, listener, &ListenerClass::onClientBuffer);
//}


} } // namespace ofx::Twitter
