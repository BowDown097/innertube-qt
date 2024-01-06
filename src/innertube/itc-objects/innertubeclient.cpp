#include "innertubeclient.h"
#include <QJsonDocument>
#include <QtNetwork/QtNetwork>

InnertubeClient::InnertubeClient(ClientType clientType, const QString& clientVersion, const QString& platform,
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
    QNetworkAccessManager* man = new QNetworkAccessManager;
    QNetworkReply* reply = man->get(QNetworkRequest(QUrl("https://www.youtube.com/")));

    QObject::connect(reply, &QNetworkReply::finished, [this, reply] {
        QByteArray response = reply->readAll();
        QString visitorBlock = response.mid(response.indexOf("visitorData") + 14);
        visitorBlock = visitorBlock.left(visitorBlock.indexOf("%3D\"") + 3);
        visitorData = visitorBlock;

        reply->deleteLater();
        reply->manager()->deleteLater();
    });

    if (clientVersion.isEmpty())
    {
        std::optional<QString> latestVersion = getLatestVersion(clientType);
        if (latestVersion.has_value())
            this->clientVersion = latestVersion.value();
        else
            qCritical() << "Failed to get latest version for client " << static_cast<int>(clientType);
    }
}

std::optional<QString> InnertubeClient::getLatestVersion(ClientType clientType)
{
    switch (clientType)
    {
    // dynamic
    case ClientType::WEB:
        return getVersionFromSwJs("https://www.youtube.com/sw.js");
    case ClientType::MWEB:
        return getVersionFromSwJs("https://m.youtube.com/sw.js");
    case ClientType::ANDROID:
    case ClientType::ANDROID_EMBEDDED_PLAYER:
        return getLatestGooglePlayVersion("youtube");
    case ClientType::IOS:
    case ClientType::IOS_LIVE_CREATION_EXTENSION:
    case ClientType::IOS_MESSAGES_EXTENSION:
        return getLatestAppStoreVersion("544007664");
    case ClientType::ANDROID_CREATOR:
        return getLatestGooglePlayVersion("youtube-creator-studio");
    case ClientType::IOS_CREATOR:
        return getLatestAppStoreVersion("888530356");
    case ClientType::ANDROID_KIDS:
        return getLatestGooglePlayVersion("youtube-kids");
    case ClientType::IOS_KIDS:
        return getLatestAppStoreVersion("936971630");
    case ClientType::ANDROID_MUSIC:
        return getLatestGooglePlayVersion("youtube-music");
    case ClientType::ANDROID_TV:
        return getLatestGooglePlayVersion("youtube-for-android-tv");
    case ClientType::IOS_MUSIC:
        return getLatestAppStoreVersion("1017492454");
    case ClientType::ANDROID_UNPLUGGED:
    case ClientType::TVHTML5_UNPLUGGED:
        return getLatestGooglePlayVersion("youtube-tv");
    case ClientType::IOS_UNPLUGGED:
        return getLatestAppStoreVersion("1193350206");
    case ClientType::WEB_REMIX:
        return getVersionFromSwJs("https://music.youtube.com/sw.js");
    case ClientType::ANDROID_TV_KIDS:
        return getLatestGooglePlayVersion("youtube-kids-for-android-tv");
    // hardcoded
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
    // default
    default:
        return std::nullopt;
    }
}

std::optional<QString> InnertubeClient::getLatestAppStoreVersion(const QString& bundleId)
{
    QNetworkAccessManager* man = new QNetworkAccessManager;
    QNetworkReply* reply = man->get(QNetworkRequest(QUrl("https://itunes.apple.com/lookup?id=" + bundleId)));

    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    QJsonValue appResult = QJsonDocument::fromJson(reply->readAll())["results"][0];
    reply->deleteLater();
    man->deleteLater();

    if (!appResult.isObject())
        return std::nullopt;

    return appResult["version"].toString();
}

std::optional<QString> InnertubeClient::getLatestGooglePlayVersion(const QString& name)
{
    QNetworkAccessManager* man = new QNetworkAccessManager;
    QNetworkReply* reply = man->get(QNetworkRequest(QUrl(QStringLiteral("https://%1.en.uptodown.com/android/download").arg(name))));

    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    static QRegularExpression softwareVersionRegex("softwareVersion\":\"([0-9\\.]+?)\"");
    QRegularExpressionMatch versionMatch = softwareVersionRegex.match(reply->readAll());

    reply->deleteLater();
    man->deleteLater();

    if (!versionMatch.hasMatch())
        return std::nullopt;

    return versionMatch.captured(1);
}

// courtesy of https://github.com/TeamNewPipe/NewPipeExtractor
std::optional<QString> InnertubeClient::getVersionFromSwJs(const QString& url)
{
    QNetworkAccessManager* man = new QNetworkAccessManager;
    QNetworkReply* reply = man->get(QNetworkRequest(QUrl(url)));

    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    static QRegularExpression clientVersionRegex("INNERTUBE_CONTEXT_CLIENT_VERSION\":\"([0-9\\.]+?)\"");
    QRegularExpressionMatch versionMatch = clientVersionRegex.match(reply->readAll());

    reply->deleteLater();
    man->deleteLater();

    if (!versionMatch.hasMatch())
        return std::nullopt;

    return versionMatch.captured(1);
}

QJsonObject InnertubeClient::toJson() const
{
    QJsonObject object {
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
