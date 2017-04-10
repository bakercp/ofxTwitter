ofxTwitter
===============

Streaming and REST Twitter Clients for [openFrameworks](http://openframeworks.cc)

Requirements
-----------

openFrameworks master branch (0.10.+)

Requires the _master_ branch following addons (and all of their dependencies):

* [ofxHTTP](https://github.com/bakercp/ofxHTTP)
  * [ofxNetworkUtils](https://github.com/bakercp/ofxNetworkUtils)
  * [ofxMediaType](https://github.com/bakercp/ofxMediaType)
  * [ofxSSLManager](https://github.com/bakercp/ofxSSLManager)
  * [ofxIO](https://github.com/bakercp/ofxIO)
    * ofxPoco _built-in_  
* [ofxGeo](https://github.com/bakercp/ofxGeo)

Twitter Credential Info
-----------------------

In order to use the Twitter API with ofxTwitter, you will need a Twitter account and a registered Twitter application in order to generate the required credential information:

* Consumer Key (API Key)
* Consumer Secret (API Secret)
* Access Token
* Access Token Secret

This information can be given to ofxTwitter via the ofxHTTP::OAuth10Credentials constructor or via loading a JSON file (recommended). A template JSON file is provided with ofxTwitter: `data/credentials.json`.

To create a Twitter app and the required credential info:

1. Create an account at [twitter.com](https://twitter.com) if do not already have one
2. Create a Twitter application on [apps.twitter.com](http://apps.twitter.com)

Setting Up OF App Data
----------------------

An OF app using ofxTwitter requires a set of files in it's `bin/data` folder:

* **credentials.json**: your Twitter app's consumer & access token information
* **ssl/cacert.pem**: a collection of trusted root certification authorities, needed for the SSL communication for the Twitter API
* **mime.types**: a list of known Internet media [MIME](https://en.wikipedia.org/wiki/MIME) types, used to determine data types when querying info from from the Twitter API

### Example Apps

For the example apps to work with th Twitter API, they must be set to use your Twitter app's credential information.

1. Open your Twitter app's page on [apps.twitter.com](http://apps.twitter.com) & choose the "Keys & Access Tokens" tab
2. Fill in your Twitter app's Consumer & Access info into your OF app's `bin/data/credentials.json` file

### Your OF App(s)

To set up the `credentials.json` file & associated data for your OF app using ofxTwitter:

1. Copy the contents of the ofxTwitter `data` folder into your OF app's `bin/data` folder
2. Open your Twitter app's page on [apps.twitter.com](http://apps.twitter.com) & choose the "Keys & Access Tokens" tab
3. Fill in your Twitter app's Consumer & Access info into your OF app's `bin/data/credentials.json` file
4. Load the credentials before making a query with an ofxTwitter client:

```c++
  client.setCredentialsFromFile("credentials.json");
```

That's it!

If you are working with multiple OF app's using the same credential info, you can just copy and reuse the same `credentials.json` file.

Keep Your Credentials Secret
----------------------------

Keep your Twitter app's secret key & access token SECRET! If someone else has the right info, they can use/misuse the Twitter API in your name and possibly have your Twitter app's access revoked!

**DO NOT let anyone else see/use your Twitter app's Consumer Secret and/or Access Token Secret!**

**DO NOT add the credentials JSON file or any source file which includes either the Consumer Secret and/or Access Token Secret to a git/GitHub repository!**

You have been warned :)

References
----------

* [Twitter API](https://dev.twitter.com/overview/api)
* [Twitter Search API](https://dev.twitter.com/rest/public/search), aka building search queries
