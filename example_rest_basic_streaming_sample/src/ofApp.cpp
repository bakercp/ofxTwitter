// =============================================================================
//
// Copyright (c) 2013-2016 Christopher Baker <http://christopherbaker.net>
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


#include "ofApp.h"


void ofApp::setup()
{
    ofSetFrameRate(30);

    // First we load credentials from a file. These can also be loaded manually
    // using the ofxTwitter::Credentials constructor.
    //
    // Developers must get their credentials after creating an app at
    // https://apps.twitter.com.
    auto credentials = ofxHTTP::OAuth10Credentials::fromFile("credentials.json");

    // Next we add our credentials to our ofxTwitter::RESTClient.
    client.setCredentials(credentials);

    // Use a default streaming request.

    ofxTwitter::StreamingRequestParameters params;

    params.setFilterLevel(ofx::Twitter::BaseFilterStreamingRequestParameters::FilterLevel::NONE);


    //41.5106340606,-88.2586669922,42.3524549195, -87.2561645508

    ofxGeo::CoordinateBounds location({ 42.3524549195, -88.2586669922 },
                                      { 41.5106340606, -87.2561645508 });

    ofxTwitter::SampleStreamingRequest request(params);

    ofxHTTP::BaseResponse response;
    ofxHTTP::Context context;

    // set up shorter timeout.
    ofxHTTP::ClientSessionSettings s = context.getClientSessionSettings();
    s.setTimeout(Poco::Timespan(10, 0));
    context.setClientSessionSettings(s);

    // Execute a basic http request.
    std::istream& istr = client.execute(request, response, context);

    ofxHTTP::HTTPUtils::dumpHeaders(response, OF_LOG_NOTICE);

    std::streamsize bufferSize = 8192;
    
    Poco::Buffer<char> buffer(bufferSize);
    std::streamsize len = 0;

    ofxIO::ByteBuffer statusBuffer;

    for (std::string line; std::getline(istr, line) && !istr.bad() && !istr.fail();)
    {
        ofJson json = ofJson::parse(line);

        if (json.is_null())
        {
            cout << "null prbly blank line" << endl;
        }
        else if (!json["delete"].is_null())
        {
//            cout << "delete" << endl;
        }
        else if (!json["text"].is_null())
        {
            cout << "text" << endl;
            ofxTwitter::Status status = ofxTwitter::Status::fromJSON(json);

            std::cout << status.text() << std::endl;
        }
        else if (!json["scrub_geo"].is_null())
        {
            cout << "scrub_geo" << endl;
        }
        else if (!json["limit"].is_null())
        {
            cout << "limit" << endl;
        }
        else if (!json["status_withheld"].is_null())
        {
            cout << "status_withheld" << endl;
        }
        else if (!json["user_withheld"].is_null())
        {
            cout << "user_withheld" << endl;
        }
        else if (!json["disconnect"].is_null())
        {
            cout << "disconnect" << endl;
        }
        else if (!json["warning"].is_null())
        {
            cout << "warning" << endl;
        }
        else if (!json["event"].is_null())
        {
            cout << "event." << endl;
        }
        else if (!json["friends"].is_null())
        {
            cout << "friends." << endl;
        }
        else if (!json["for_user"].is_null())
        {
            cout << "for_user update." << endl;
        }
        else if (!json["control"].is_null())
        {
            cout << "control update." << endl;
        }
        else
        {
            std::cout << json.dump(4) << std::endl;
        }
    }

}


void ofApp::draw()
{
    ofBackgroundGradient(ofColor::white, ofColor::black);
    ofDrawBitmapStringHighlight("See console for output.", 30, 30);
}
