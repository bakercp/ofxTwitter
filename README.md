# ofxTwitter

## Description

Streaming and REST Twitter Clients for [openFrameworks](http://openframeworks.cc)

## Features

-   Twitter Streaming API client.
-   Twitter [Search API](https://dev.twitter.com/rest/public/search) client.
-   Easily extensible.
-   Many [API](https://dev.twitter.com/overview/api) features implemented (e.g. Search, Tweet, Media Upload).

## Getting Started

To get started, generate the example project files using the openFrameworks [Project Generator](http://openframeworks.cc/learning/01_basics/how_to_add_addon_to_project/).

## Documentation

API documentation can be found here.

### Twitter Credentials

In order to use the Twitter API with `ofxTwitter`, you will need a Twitter developer account and a registered Twitter application in order to generate the required credential information. To do this:

1.  Create an account at [twitter.com](https://twitter.com) if do not already have one.
2.  Create a Twitter application on [apps.twitter.com](http://apps.twitter.com).
3.  Once you have created an application, choose the "Keys & Access Tokens" tab and make note of the following credential items:

*   Consumer Key (API Key)
*   Consumer Secret (API Secret)
*   Access Token
*   Access Token Secret

These credentials can be used with `ofxTwitter` programmatically or by loading a JSON file. A template JSON credentials file is provided with each example in `ofxTwitter`: `bin/data/credentials.json`. If you are working with multiple OF apps using the same credential info, you can just copy and reuse the same `credentials.json` file.

Note that the credentials are loaded with this code, usually in the `ofApp::setup()` method:

```c++
  client.setCredentialsFromFile("credentials.json");
```

Alternatively you can load credentials programmatically with the following:

```c++
    ofxHTTP::OAuth10Credentials credentials("YOUR_CONSUMER_KEY_HERE",
                                            "YOUR_CONSUMER_SECRET_HERE",
                                            "YOUR_ACCESS_TOKEN_HERE",
                                            "YOUR_ACCESS_TOKEN_SECRET_HERE");
    client.setCredentials(credentials)
```

### Creating a Twitter Application

To create an application with `ofxTwitter` you need credentials (see above) and (optionally) you need an SSL certificate bundle (See [ofxSSLManager](https://github.com/bakercp/ofxSSLManager/blob/master/README.md) for more info) in your `bin/data` folder. You will likely need to include the following files:

*   `credentials.json`: your Twitter app's consumer & access token information.
*   `ssl/cacert.pem`: a collection of trusted root certification authorities, needed for the SSL communication for the Twitter API.


### Keep Your Credentials Secret

Be careful not to upload your `credentials.json` file to a public Github repository. If you do, don't worry -- you can easily log on to [apps.twitter.com](http://apps.twitter.com) and revoke your compromised credentials and generate new ones.

## Compatibility

### Branches

The `stable` branch of this repository is meant to be compatible with the openFrameworks [stable branch](https://github.com/openframeworks/openFrameworks/tree/stable), which corresponds to the latest official openFrameworks release.

The `master` branch of this repository is meant to be compatible with the openFrameworks [master branch](https://github.com/openframeworks/openFrameworks/tree/master).

Some past openFrameworks releases are supported via [releases](../../releases/), but only the [stable branch](../../tree/stable) and the [master branch](../../tree/master) are actively supported.

### Requirements
-   [ofxIO](https://github.com/bakercp/ofxIO)
-   ofxPoco (included with openFrameworks)
-   [ofxMediaType](https://github.com/bakercp/ofxMediaType)
-   [ofxSSLManager](https://github.com/bakercp/ofxSSLManager)
-   [ofxNetworkUtils](https://github.com/bakercp/ofxNetworkUtils)
-   [ofxGeo](https://github.com/bakercp/ofxGeo)

## Versioning

This project uses [Semantic Versioning](http://semver.org/), although strict adherence will only come into effect at version 1.0.0.

## Licensing

See [LICENSE.md](LICENSE.md).

## Contributing

Pull Requests are always welcome, so if you make any improvements please feel free to float them back upstream :)

1.  Fork this repository.
2.  Create your feature branch (`git checkout -b my-new-feature`).
3.  Commit your changes (`git commit -am 'Add some feature'`).
4.  Push to the branch (`git push origin my-new-feature`).
5.  Create new Pull Request.
