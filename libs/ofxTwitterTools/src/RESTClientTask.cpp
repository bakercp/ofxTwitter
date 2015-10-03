//// =============================================================================
////
//// Copyright (c) 2009-2015 Christopher Baker <http://christopherbaker.net>
////
//// Permission is hereby granted, free of charge, to any person obtaining a copy
//// of this software and associated documentation files (the "Software"), to deal
//// in the Software without restriction, including without limitation the rights
//// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//// copies of the Software, and to permit persons to whom the Software is
//// furnished to do so, subject to the following conditions:
////
//// The above copyright notice and this permission notice shall be included in
//// all copies or substantial portions of the Software.
////
//// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//// THE SOFTWARE.
////
//// =============================================================================
//
//
//#include "ofx/Twitter/RESTClient.h"
//#include "ofx/Twitter/Deserializer.h"
//#include "ofx/HTTP/GetRequest.h"
//
//
//namespace ofx {
//namespace Twitter {
//
//
//RESTClientTask::RESTClientTask()
//{
//}
//
//
//RESTClientTask::RESTClientTask(const Credentials& credentials):
//    BaseTwitterClient(credentials)
//{
//}
//
//
//RESTClient::~RESTClient()
//{
//}
//
//
//SearchResult RESTClient::search(const SearchQuery& query)
//{
//    HTTP::GetRequest request("https://api.twitter.com/1.1/search/tweets.json",
//                             Poco::Net::HTTPRequest::HTTP_1_1);
//
//    request.addFormFields(query);
//
//    HTTP::BaseResponse response;
//
//    Json::Value json;
//
//    execute(request, response, json);
//
//    SearchResult searchResult(response.getStatus());
//
//    Deserializer::deserialize(json, searchResult);
//
//    return searchResult;
//}
//
//
//void RESTClient::execute(HTTP::BaseRequest& request,
//                         HTTP::BaseResponse& response,
//                         Json::Value& results)
//{
//    // Execute the request.
//    std::istream& responseStream = BaseClient::execute(request,
//                                                       response,
//                                                       _context);
//
//    std::string buffer;
//
//    Json::Reader reader;
//
//    Poco::StreamCopier::copyToString(responseStream, buffer);
//
//    if (!reader.parse(buffer, results))
//    {
//        throw Poco::SyntaxException(reader.getFormattedErrorMessages());
//    }
//}
//
//
//} } // namespace ofx::Twitter
