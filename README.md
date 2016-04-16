ofxTwitterTools
===============

Streaming and REST Twitter Clients for [openFrameworks](http://openframeworks.cc)

Requirements
-----------

openFrameworks 0.9.0+

Requires the following addons (and all of their dependencies):

* [ofxHTTP](https://github.com/bakercp/ofxHTTP)
* [ofxGeo](https://github.com/bakercp/ofxGeo)
* [ofxJSON](https://github.com/jefftimesten/ofxJSON)

Twitter Credential Info
-----------------------

In order to use the Twitter API with ofxTwitterTools, you will need a Twitter account and a registered Twitter application in order to generate the required credential information:

* Consumer Key (API Key)
* Consumer Secret (API Secret)
* Access Token
* Access Token Secret

This information can be given to ofxTwitterTools via the ofxTwitter::Credentials constructor or via loading a JSON file (recommended). A template json file is provided with ofxTwitterTools: `data/credentials.json`.

To create a Twitter app and the required credential info:

1. Create an account at [twitter.com](https://twitter.com) if do not already have one 
2. Create a Twitter application on [apps.twitter.com](http://apps.twitter.com)

Setting Up OF App Data
----------------------

An OF app using ofxTwitterTools requires a set of files in it's `bin/data` folder:

* **credentials.json**: your Twitter app's consumer & access token information
* **ssl/cacert.pem**: a collection of trusted root certification authorities, needed for the SSL communication for the Twitter API
* **mime.types**: a list of known internet media [MIME](https://en.wikipedia.org/wiki/MIME) types, used to determine data types when querying info from from the Twitter API

### Example Apps


For the example apps to wotj with th Twitter api, they must be set to use your Twitter app's credential information.

1. Open your Twitter app's page on [apps.twitter.com](http://apps.twitter.com) & choose the "Keys & Access Tokens" tab
2. Fill in your Twitter app's Consumer & Access info into your OF app's `bin/data/credentials.json` file

### Your OF App(s)

To set up the `credentials.json` file & associated data for your OF app using ofxTwitterTools:

1. Copy the contents of the ofxTwitterTools `data` folder into your OF app's `bin/data` folder
2. Open your Twitter app's page on [apps.twitter.com](http://apps.twitter.com) & choose the "Keys & Access Tokens" tab
3. Fill in your Twitter app's Consumer & Access info into your OF app's `bin/data/credentials.json` file
4. Load the credentials before making a query with an ofxTwitterTools client:

    ofxTwitter::Credentials credentials = ofxTwitter::Credentials::fromFile("credentials.json");
    client.setCredentials(credentials);

That's it!

If you are working with multiple OF app's using the same credential info, you can just copy and reuse the same `credentials.json` file.

Keep Your Credentials Secret
----------------------------

Keep your Twitter appp's secret key & access token SECRET! If someone else has the right info, they can use/misuse the Twitter API in your name and possibly have your Twitter's app's access revoked!

**DO NOT let anyone else see/use your Twitter app's Consumer Secret and/or Access Token Secret!**

**DO NOT add the credentials JSON file or any source file which includes either the Consumer Secret and/or Access Token Secret to a git/GitHub repository!** 

You have been warned :)

References
----------

[Twitter API](https://dev.twitter.com/overview/api)
