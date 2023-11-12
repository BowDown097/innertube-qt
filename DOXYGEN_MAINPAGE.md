A Qt library to interface with YouTube's InnerTube API.

## Getting Started {#GettingStarted}
To get started, use @ref InnerTube::createContext. This example code will create an ideal, working context for you:
```cpp
InnerTube::instance().createContext(InnertubeClient(InnertubeClient::ClientType::WEB, "2.20230718.01.00", "DESKTOP"));
```
Here, a context is created around a client of the WEB type, version 2.20230718.01.00, on the DESKTOP platform. If you're not using the WEB client, you probably want to take a look at the [Raw Requests](@ref RawRequests) section.<br><br>

To make a request, use @ref InnerTube::get. This example code provides a good way to test if things are working:
```cpp
InnertubeReply* reply = InnerTube::instance().get<InnertubeEndpoints::Next>("dQw4w9WgXcQ");
connect(reply, qOverload<const InnertubeEndpoints::Next&>(&InnertubeReply::finished), this, [](const auto& next) {
    qDebug() << next.response.primaryInfo.title.text;
});
```
Here, a request is made to the @ref InnertubeEndpoints::Next "Next endpoint" supplied with the video ID for [the classic Rick Roll video](https://www.youtube.com/watch?v=dQw4w9WgXcQ).
Once the request finishes, the response is captured and the video title is printed (which should be "Rick Astley - Never Gonna Give You Up (Official Music Video)").

## Raw Requests {#RawRequests}
The WEB client is the only client officially supported by this library. If you are using other clients, raw requests will likely be the only way to get data without any errors, with the exception of the @ref InnertubeEndpoints::Player "Player", @ref InnertubeEndpoints::SendMessage "SendMessage", @ref InnertubeEndpoints::Subscribe "Subscribe", and @ref InnertubeEndpoints::UnseenCount "UnseenCount" endpoints on most clients (and maybe more from client to client).

To make a **raw** request, use @ref InnerTube::getRaw. Like before, here's example code for getting the Rick Roll video's data, with client setup too as a bonus. We will be using the obscure ANDROID\_TESTSUITE client for this example.
```cpp
InnerTube::instance().createContext(InnertubeClient(InnertubeClient::ClientType::ANDROID_TESTSUITE, "1.9", "MOBILE"));

InnertubeReply* reply = InnerTube::instance().getRaw<InnertubeEndpoints::Next>({
    { "playbackContext", InnertubePlaybackContext(false, "").toJson() },
    { "videoId", "dQw4w9WgXcQ" }
});

connect(reply, &InnertubeReply::finishedRaw, this, [](const QJsonValue& v) {
    qDebug() << InnertubeObjects::InnertubeString(v["contents"]["singleColumnWatchNextResults"]["results"]["results"]["contents"][0]["itemSectionRenderer"]["contents"][0]["videoMetadataRenderer"]["title"]).text;
});
```
This does the same thing as the code in the [Getting Started](@ref GettingStarted) section.

## Authenticating (easily)
If you wish to support logging in, you can use the authentication methods in the @ref InnerTube class.

To get started, use @ref InnerTube::authenticate. This will open up a browser window on YouTube's login page that captures the necessary credentials. Once all of the necessary credentials have been captured, the signal @ref InnertubeAuthStore::authenticateSuccess is emitted, and you can do whatever you want beyond that point. The method @ref InnerTube::authStore returns the @ref InnertubeAuthStore in question.<br>
**Note that this method depends on Qt Web Engine. See the [Authenticating Manually](@ref AuthenticatingManually) section if you wish to not use Qt Web Engine.**

If you want to dive deeper, have a look at the @ref InnertubeAuthStore class.

## Authenticating (manually) {#AuthenticatingManually}
**Be warned, this not an easy process. Also, this guide will be for Firefox, but there will likely be a lot of overlap with Chromium-based browsers anyway.**

### Getting the Credentials
1. Go to the YouTube home page.
2. Open up Developer Tools (pressing Ctrl+Shift+I or F12 works, or you can use the browser menu) and go to the Network tab.
3. In the "Filter URLs" bar, type "youtubei/v1" and select any result **except for ones which contain "log_event".**
4. In the "Headers" section, in the "Filter Headers" bar, type "cookie" and look for the entry that's just called "Cookie". Right click the entry and click "Copy Value".
5. Inside of what you just copied, look for the values for APISID, HSID, SAPISID, SID, SSID, and VISITOR\_INFO1\_LIVE. For example, in VISITOR\_INFO1\_LIVE=xxx, the value would be xxx.

### Putting It Into the Library
To feed this data into the library, create a QJsonObject like so:
```cpp
QJsonObject obj {
    { "apisid", "<YOUR APISID HERE>" },
    { "hsid", "<YOUR HSID HERE>" },
    { "sapisid", "<YOUR SAPISID HERE>" },
    { "sid", "<YOUR SID HERE>" },
    { "ssid", "<YOUR SSID HERE>" },
    { "visitorInfo", "<YOUR VISITOR_INFO1_LIVE HERE>" }
};
```
Then, see steps 2 and 3 in [Restoring Authentication Data](@ref RestoringAuthenticationData).

## Restoring Authentication Data {#RestoringAuthenticationData}
Some facilities have been provided for making this easier. Here's the way I recommend doing it:
1. Once the user has authenticated successfully, get the credentials as a JSON object using @ref InnertubeAuthStore::toJson and save it to a JSON file on the system.
2. To restore the data, read the JSON file back to a QJsonObject, then provide this QJsonObject to @ref InnerTube::authenticateFromJson.
3. To check if this was successful, use @ref InnerTube::hasAuthenticated.
