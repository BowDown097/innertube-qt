#include "innertubeclient.h"
#include "http.h"
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>

InnertubeClient::InnertubeClient(ClientType clientType, const QString& clientVersion,
                                 bool useClientVersionAsFallback, const QString& platform,
                                 const QString& userAgent, const QString& browserName, const QString& browserVersion,
                                 const QString& userInterfaceTheme, const QString& clientFormFactor,
                                 const InnertubeConfigInfo& configInfo, const QString& deviceMake, const QString& deviceModel,
                                 const QString& gl, const QString& hl, const QString& originalUrl, const QString& osName,
                                 const QString& osVersion, const QString& remoteHost, int screenDensityFloat,
                                 int screenPixelDensity, const QString& timeZone)
    : browserName(browserName),
      browserVersion(browserVersion),
      clientFormFactor(clientFormFactor),
      clientType(clientType),
      clientVersion(clientVersion),
      configInfo(configInfo),
      deviceMake(deviceMake),
      deviceModel(deviceModel),
      gl(gl),
      hl(hl),
      originalUrl(originalUrl),
      osName(osName),
      osVersion(osVersion),
      platform(platform),
      remoteHost(remoteHost),
      screenDensityFloat(screenDensityFloat),
      screenPixelDensity(screenPixelDensity),
      timeZone(timeZone),
      userAgent(userAgent),
      userInterfaceTheme(userInterfaceTheme)
{
    if (useClientVersionAsFallback)
        this->clientVersion = clientVersion;

    const HttpReply* reply = Http::instance().get(QUrl("https://www.youtube.com/"));

    QEventLoop loop;
    QObject::connect(reply, &HttpReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    QString visitorBlock = reply->body().mid(reply->body().indexOf("visitorData") + 14);
    visitorBlock = visitorBlock.left(visitorBlock.indexOf("%3D\"") + 3);
    visitorData = visitorBlock;

    if (useClientVersionAsFallback || clientVersion.isEmpty())
    {
        QString latestVersion = getLatestVersion(clientType);
        if (!latestVersion.isEmpty())
            this->clientVersion = latestVersion;
        else if (useClientVersionAsFallback)
            qWarning() << "Failed to get latest version for client " << resolveClientName(clientType) << ": using fallback version " << clientVersion;
        else
            qCritical() << "Failed to get latest version for client " << resolveClientName(clientType);
    }
}

QString InnertubeClient::getLatestVersion(ClientType clientType)
{
    switch (clientType)
    {
    case ClientType::WEB:
    {
        QString ver = getVersionFromPageBody("https://www.youtube.com/sw.js");
        if (ver.isEmpty())
        {
            qDebug() << "Failed to get Innertube client version from service worker. Falling back to results page.";
            ver = getVersionFromPageBody("https://www.youtube.com/results?search_query=");
        }
        return ver;
    }
    case ClientType::MWEB:
    {
        QString ver = getVersionFromPageBody("https://m.youtube.com/sw.js");
        if (ver.isEmpty())
        {
            qDebug() << "Failed to get Innertube client version from service worker. Falling back to results page.";
            ver = getVersionFromPageBody("https://m.youtube.com/results?search_query=");
        }
        return ver;
    }
    case ClientType::ANDROID:
    case ClientType::ANDROID_EMBEDDED_PLAYER:
        return getVersionFromGooglePlay("youtube");
    case ClientType::IOS:
    case ClientType::IOS_LIVE_CREATION_EXTENSION:
    case ClientType::IOS_MESSAGES_EXTENSION:
        return getVersionFromAppStore("544007664");
    case ClientType::TVHTML5:
    {
        QString ver = getVersionFromPageBody("https://www.youtube.com/tv/sw.js");
        if (ver.isEmpty())
        {
            qDebug() << "Failed to get Innertube client version from service worker. Falling back to tv_config.";
            ver = getVersionFromPageBody("https://www.youtube.com/tv_config?action_get_config=true");
        }
        return ver;
    }
    case ClientType::ANDROID_CREATOR:
        return getVersionFromGooglePlay("youtube-creator-studio");
    case ClientType::IOS_CREATOR:
        return getVersionFromAppStore("888530356");
    case ClientType::ANDROID_KIDS:
        return getVersionFromGooglePlay("youtube-kids");
    case ClientType::IOS_KIDS:
        return getVersionFromAppStore("936971630");
    case ClientType::ANDROID_MUSIC:
        return getVersionFromGooglePlay("youtube-music");
    case ClientType::ANDROID_TV:
        return getVersionFromGooglePlay("youtube-for-android-tv");
    case ClientType::IOS_MUSIC:
        return getVersionFromAppStore("1017492454");
    case ClientType::ANDROID_UNPLUGGED:
    case ClientType::TVHTML5_UNPLUGGED:
        return getVersionFromGooglePlay("youtube-tv");
    case ClientType::IOS_UNPLUGGED:
        return getVersionFromAppStore("1193350206");
    case ClientType::WEB_EMBEDDED_PLAYER:
        return getVersionFromPageBody("https://www.youtube.com/embed/abcdefg"); // just use a bogus embed page
    case ClientType::WEB_REMIX: {
        QString ver = getVersionFromPageBody("https://music.youtube.com/sw.js");
        if (ver.isEmpty())
        {
            qDebug() << "Failed to get Innertube client version from service worker. Falling back to home page.";
            ver = getVersionFromPageBody("https://music.youtube.com/");
        }
        return ver;
    }
    case ClientType::ANDROID_TV_KIDS:
        return getVersionFromGooglePlay("youtube-kids-for-android-tv");
    case ClientType::TVLITE:
        return "2";
    case ClientType::TVANDROID:
    case ClientType::XBOXONEGUIDE:
    case ClientType::TVAPPLE:
    case ClientType::WEB_MUSIC:
    case ClientType::IOS_UPTIME:
    case ClientType::TVHTML5_SIMPLY:
        return "1.0";
    case ClientType::ANDROID_VR:
    case ClientType::TV_UNPLUGGED_ANDROID:
        return "1.37";
    case ClientType::ANDROID_TESTSUITE:
        return "1.9";
    case ClientType::WEB_MUSIC_ANALYTICS:
        return "0.2";
    case ClientType::ANDROID_LITE:
        return "3.26.1";
    case ClientType::WEB_UNPLUGGED:
    case ClientType::TV_UNPLUGGED_CAST:
    case ClientType::WEB_HEROES:
    case ClientType::WEB_UNPLUGGED_ONBOARDING:
    case ClientType::WEB_UNPLUGGED_OPS:
    case ClientType::WEB_UNPLUGGED_PUBLIC:
    case ClientType::TVHTML5_VR:
    case ClientType::MUSIC_INTEGRATIONS:
    case ClientType::TVHTML5_YONGLE:
    case ClientType::GOOGLE_ASSISTANT:
    case ClientType::WEB_INTERNAL_ANALYTICS:
    case ClientType::GOOGLE_MEDIA_ACTIONS:
    case ClientType::IOS_PRODUCER:
    case ClientType::GOOGLE_LIST_RECS:
    case ClientType::MEDIA_CONNECT_FRONTEND:
        return "0.1";
    case ClientType::WEB_EXPERIMENTS:
        return "1";
    case ClientType::TVHTML5_CAST:
        return "1.1";
    case ClientType::TVHTML5_AUDIO:
    case ClientType::TVHTML5_SIMPLY_EMBEDDED_PLAYER:
        return "2.0";
    case ClientType::WEB_PHONE_VERIFICATION:
        return "1.0.0";
    default:
        return QString();
    }
}

QString InnertubeClient::getVersionFromAppStore(const QString& bundleId)
{
    const HttpReply* reply = Http::instance().get(QUrl("https://itunes.apple.com/lookup?id=" + bundleId));

    QEventLoop loop;
    QObject::connect(reply, &HttpReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    QJsonValue appResult = QJsonDocument::fromJson(reply->body())["results"][0];
    return appResult["version"].toString();
}

QString InnertubeClient::getVersionFromGooglePlay(const QString& name)
{
    const HttpReply* reply = Http::instance().get(QUrl(QStringLiteral("https://%1.en.uptodown.com/android/download").arg(name)));

    QEventLoop loop;
    QObject::connect(reply, &HttpReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    static QRegularExpression softwareVersionRegex("softwareVersion\":\"([0-9\\.]+?)\"");
    return softwareVersionRegex.match(reply->body()).captured(1);
}

// mostly courtesy of https://github.com/TeamNewPipe/NewPipeExtractor
QString InnertubeClient::getVersionFromPageBody(const QString& url)
{
    const HttpReply* reply = Http::instance().get(QUrl(url));

    QEventLoop loop;
    QObject::connect(reply, &HttpReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    static QRegularExpression clientVersionRegex(
        "(INNERTUBE_CONTEXT_CLIENT_VERSION|innertubeContextClientVersion)\":\"([0-9\\.]+?)\"");
    return clientVersionRegex.match(reply->body()).captured(2);
}

QString InnertubeClient::resolveClientName(ClientType clientType)
{
    switch (clientType)
    {
    case ClientType::WEB: return "WEB";
    case ClientType::MWEB: return "MWEB";
    case ClientType::ANDROID: return "ANDROID";
    case ClientType::IOS: return "IOS";
    case ClientType::TVHTML5: return "TVHTML5";
    case ClientType::TVLITE: return "TVLITE";
    case ClientType::TVANDROID: return "TVANDROID";
    case ClientType::XBOXONEGUIDE: return "XBOXONEGUIDE";
    case ClientType::ANDROID_CREATOR: return "ANDROID_CREATOR";
    case ClientType::IOS_CREATOR: return "IOS_CREATOR";
    case ClientType::TVAPPLE: return "TVAPPLE";
    case ClientType::ANDROID_KIDS: return "ANDROID_KIDS";
    case ClientType::IOS_KIDS: return "IOS_KIDS";
    case ClientType::ANDROID_MUSIC: return "ANDROID_MUSIC";
    case ClientType::ANDROID_TV: return "ANDROID_TV";
    case ClientType::IOS_MUSIC: return "IOS_MUSIC";
    case ClientType::MWEB_TIER_2: return "MWEB_TIER_2";
    case ClientType::ANDROID_VR: return "ANDROID_VR";
    case ClientType::ANDROID_UNPLUGGED: return "ANDROID_UNPLUGGED";
    case ClientType::ANDROID_TESTSUITE: return "ANDROID_TESTSUITE";
    case ClientType::WEB_MUSIC_ANALYTICS: return "WEB_MUSIC_ANALYTICS";
    case ClientType::IOS_UNPLUGGED: return "IOS_UNPLUGGED";
    case ClientType::ANDROID_LITE: return "ANDROID_LITE";
    case ClientType::IOS_EMBEDDED_PLAYER: return "IOS_EMBEDDED_PLAYER";
    case ClientType::WEB_UNPLUGGED: return "WEB_UNPLUGGED";
    case ClientType::WEB_EXPERIMENTS: return "WEB_EXPERIMENTS";
    case ClientType::TVHTML5_CAST: return "TVHTML5_CAST";
    case ClientType::ANDROID_EMBEDDED_PLAYER: return "ANDROID_EMBEDDED_PLAYER";
    case ClientType::WEB_EMBEDDED_PLAYER: return "WEB_EMBEDDED_PLAYER";
    case ClientType::TVHTML5_AUDIO: return "TVHTML5_AUDIO";
    case ClientType::TV_UNPLUGGED_CAST: return "TV_UNPLUGGED_CAST";
    case ClientType::TVHTML5_KIDS: return "TVHTML5_KIDS";
    case ClientType::WEB_HEROES: return "WEB_HEROES";
    case ClientType::WEB_MUSIC: return "WEB_MUSIC";
    case ClientType::WEB_CREATOR: return "WEB_CREATOR";
    case ClientType::TV_UNPLUGGED_ANDROID: return "TV_UNPLUGGED_ANDROID";
    case ClientType::IOS_LIVE_CREATION_EXTENSION: return "IOS_LIVE_CREATION_EXTENSION";
    case ClientType::TVHTML5_UNPLUGGED: return "TVHTML5_UNPLUGGED";
    case ClientType::IOS_MESSAGES_EXTENSION: return "IOS_MESSAGES_EXTENSION";
    case ClientType::WEB_REMIX: return "WEB_REMIX";
    case ClientType::IOS_UPTIME: return "IOS_UPTIME";
    case ClientType::WEB_UNPLUGGED_ONBOARDING: return "WEB_UNPLUGGED_ONBOARDING";
    case ClientType::WEB_UNPLUGGED_OPS: return "WEB_UNPLUGGED_OPS";
    case ClientType::WEB_UNPLUGGED_PUBLIC: return "WEB_UNPLUGGED_PUBLIC";
    case ClientType::TVHTML5_VR: return "TVHTML5_VR";
    case ClientType::ANDROID_TV_KIDS: return "ANDROID_TV_KIDS";
    case ClientType::TVHTML5_SIMPLY: return "TVHTML5_SIMPLY";
    case ClientType::WEB_KIDS: return "WEB_KIDS";
    case ClientType::MUSIC_INTEGRATIONS: return "MUSIC_INTEGRATIONS";
    case ClientType::TVHTML5_YONGLE: return "TVHTML5_YONGLE";
    case ClientType::GOOGLE_ASSISTANT: return "GOOGLE_ASSISTANT";
    case ClientType::TVHTML5_SIMPLY_EMBEDDED_PLAYER: return "TVHTML5_SIMPLY_EMBEDDED_PLAYER";
    case ClientType::WEB_INTERNAL_ANALYTICS: return "WEB_INTERNAL_ANALYTICS";
    case ClientType::WEB_PARENT_TOOLS: return "WEB_PARENT_TOOLS";
    case ClientType::GOOGLE_MEDIA_ACTIONS: return "GOOGLE_MEDIA_ACTIONS";
    case ClientType::WEB_PHONE_VERIFICATION: return "WEB_PHONE_VERIFICATION";
    case ClientType::IOS_PRODUCER: return "IOS_PRODUCER";
    case ClientType::TVHTML5_FOR_KIDS: return "TVHTML5_FOR_KIDS";
    case ClientType::GOOGLE_LIST_RECS: return "GOOGLE_LIST_RECS";
    case ClientType::MEDIA_CONNECT_FRONTEND: return "MEDIA_CONNECT_FRONTEND";
    default: return QString();
    }
}

QJsonObject InnertubeClient::toJson() const
{
    QJsonObject object = {
        { "browserName", browserName },
        { "browserVersion", browserVersion },
        { "clientFormFactor", clientFormFactor },
        { "clientName", static_cast<int>(clientType) },
        { "clientVersion", clientVersion },
        { "configInfo", configInfo.toJson() },
        { "deviceMake", deviceMake },
        { "deviceModel", deviceModel },
        { "gl", gl },
        { "hl", hl },
        { "originalUrl", originalUrl },
        { "osName", osName },
        { "osVersion", osVersion },
        { "remoteHost", remoteHost },
        { "screenDensityFloat", screenDensityFloat },
        { "screenPixelDensity", screenPixelDensity },
        { "timeZone", timeZone },
        { "userAgent", userAgent },
        { "userInterfaceTheme", userInterfaceTheme },
        { "visitorData", visitorData }
    };

    if (!platform.isEmpty())
        object.insert("platform", platform);

    return object;
}
