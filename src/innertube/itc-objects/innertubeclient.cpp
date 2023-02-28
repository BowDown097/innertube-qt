#include "innertubeclient.h"
#include "httplib.h"

InnertubeClient::InnertubeClient(const QString& clientName, const QString& clientVersion, const QString& platform, const QString& userAgent,
                                 const QString& browserName, const QString& browserVersion, const QString& userInterfaceTheme,
                                 const QString& clientFormFactor, const InnertubeConfigInfo& configInfo, const QString& deviceMake,
                                 const QString& deviceModel, const QString& gl, const QString& hl, const QString& originalUrl, const QString& osName,
                                 const QString& osVersion, const QString& remoteHost, int screenDensityFloat, int screenPixelDensity,
                                 const QString& timeZone)
    : browserName(browserName),
      browserVersion(browserVersion),
      clientFormFactor(clientFormFactor),
      clientName(clientName),
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
    // get home page data
    httplib::Client cli("https://www.youtube.com");
    httplib::Result res = cli.Get("/");
    QString hpData = QString::fromStdString(res->body);

    // get/set visitor data
    QString visitorBlock = hpData.mid(hpData.indexOf("visitorData") + 14);
    visitorBlock = visitorBlock.left(visitorBlock.indexOf("%3D\"") + 3);
    visitorData = visitorBlock;
}

QJsonObject InnertubeClient::toJson() const
{
    QJsonObject object {
        { "browserName", browserName },
        { "browserVersion", browserVersion },
        { "clientFormFactor", clientFormFactor },
        { "clientName", clientName },
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
