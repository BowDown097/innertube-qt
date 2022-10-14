#include "innertubeclient.h"
#include "CurlEasy.h"

InnertubeClient::InnertubeClient(const QString& clientName, const QString& clientVersion, const QString& platform, const QString& userInterfaceTheme,
                                 const QString& browserName, const QString& browserVersion, const QString& clientFormFactor,
                                 const InnertubeConfigInfo& configInfo, const QString& deviceMake, const QString& deviceModel, const QString& gl,
                                 const QString& hl, const QString& originalUrl, const QString& osName, const QString& osVersion,
                                 const QString& remoteHost, int screenDensityFloat, int screenPixelDensity, const QString& timeZone,
                                 const QString& userAgent)
    : browserName(browserName), browserVersion(browserVersion), clientFormFactor(clientFormFactor), clientName(clientName), clientVersion(clientVersion),
      deviceMake(deviceMake), deviceModel(deviceModel), gl(gl), hl(hl), originalUrl(originalUrl), osName(osName), osVersion(osVersion), platform(platform),
      remoteHost(remoteHost), timeZone(timeZone), userAgent(userAgent), userInterfaceTheme(userInterfaceTheme), configInfo(configInfo),
      screenDensityFloat(screenDensityFloat), screenPixelDensity(screenPixelDensity)
{
    // get home page data
    QString hpData;
    CurlEasy* easy = new CurlEasy;
    easy->set(CURLOPT_URL, "https://www.youtube.com");
    easy->setWriteFunction([&hpData](char* d, size_t size)->size_t { hpData.append(d); return size; });
    easy->perform();
    QEventLoop event;
    QObject::connect(easy, &CurlEasy::done, &event, &QEventLoop::quit);
    event.exec();
    easy->deleteLater();

    // get/set visitor data
    QString visitorBlock = hpData.mid(hpData.indexOf("visitorData") + 14);
    visitorBlock = visitorBlock.left(visitorBlock.indexOf("%3D\"") + 3);
    visitorData = visitorBlock;
}

QJsonObject InnertubeClient::toJson() const
{
    return {
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
        { "platform", platform },
        { "remoteHost", remoteHost },
        { "screenDensityFloat", screenDensityFloat },
        { "screenPixelDensity", screenPixelDensity },
        { "timeZone", timeZone },
        { "userAgent", userAgent },
        { "userInterfaceTheme", userInterfaceTheme },
        { "visitorData", visitorData }
    };
}
