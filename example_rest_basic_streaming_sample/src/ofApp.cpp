//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofApp.h"


void ofApp::setup()
{
    ofSetFrameRate(30);

    // First we load credentials from a file. These can also be loaded manually
    // using the ofxTwitter::Credentials constructor.
    //
    // Developers must get their credentials after creating an app at
    // https://apps.twitter.com.
    auto credentials = ofxHTTP::OAuth10Credentials::fromFile("NetworkedObject.json");

    // Next we add our credentials to our ofxTwitter::RESTClient.
    client.setCredentials(credentials);

    // Use a default streaming request.

    ofxTwitter::StreamingRequestParameters params;

    params.setFilterLevel(ofx::Twitter::BaseFilterStreamingRequestParameters::FilterLevel::NONE);


    //41.5106340606,-88.2586669922,42.3524549195, -87.2561645508

    ofxGeo::CoordinateBounds location({ 42.3524549195, -88.2586669922 },
                                      { 41.5106340606, -87.2561645508 });

    ofxTwitter::SampleStreamingRequest request(params);

    // set up shorter timeout.
    ofxHTTP::ClientSessionSettings s = client.context().getClientSessionSettings();
    s.setTimeout(Poco::Timespan(10, 0));
    client.context().setClientSessionSettings(s);

    // Execute a basic http request.

    auto response = client.execute(request);

    ofxHTTP::HTTPUtils::dumpHeaders(*response, OF_LOG_NOTICE);

    if (!response->isSuccess())
    {
        if (response->isBufferable())
        {
            std::cout << response->buffer().getText() << std::endl;
            return;
        }
    }

    std::cout << response->isBufferable() << std::endl;

    auto& istr = response->stream();

    Poco::StreamCopier::copyStream(istr, std::cout);

//
//    std::streamsize bufferSize = 8192;
//    
//    Poco::Buffer<char> buffer(bufferSize);
//    std::streamsize len = 0;
//
//    ofxIO::ByteBuffer statusBuffer;
//
//    for (std::string line; std::getline(istr, line) && !istr.bad() && !istr.fail();)
//    {
//        ofJson json = ofJson::parse(line);
//
//        if (json.is_null())
//        {
//            cout << "null prbly blank line" << endl;
//        }
//        else if (!json["delete"].is_null())
//        {
////            cout << "delete" << endl;
//        }
//        else if (!json["text"].is_null())
//        {
//            cout << "text" << endl;
//            ofxTwitter::Status status = ofxTwitter::Status::fromJSON(json);
//
//            std::cout << status.text() << std::endl;
//        }
//        else if (!json["scrub_geo"].is_null())
//        {
//            cout << "scrub_geo" << endl;
//        }
//        else if (!json["limit"].is_null())
//        {
//            cout << "limit" << endl;
//        }
//        else if (!json["status_withheld"].is_null())
//        {
//            cout << "status_withheld" << endl;
//        }
//        else if (!json["user_withheld"].is_null())
//        {
//            cout << "user_withheld" << endl;
//        }
//        else if (!json["disconnect"].is_null())
//        {
//            cout << "disconnect" << endl;
//        }
//        else if (!json["warning"].is_null())
//        {
//            cout << "warning" << endl;
//        }
//        else if (!json["event"].is_null())
//        {
//            cout << "event." << endl;
//        }
//        else if (!json["friends"].is_null())
//        {
//            cout << "friends." << endl;
//        }
//        else if (!json["for_user"].is_null())
//        {
//            cout << "for_user update." << endl;
//        }
//        else if (!json["control"].is_null())
//        {
//            cout << "control update." << endl;
//        }
//        else
//        {
//            std::cout << json.dump(4) << std::endl;
//        }
//    }

}


void ofApp::draw()
{
    ofBackgroundGradient(ofColor::white, ofColor::black);
    ofDrawBitmapStringHighlight("See console for output.", 30, 30);
}
