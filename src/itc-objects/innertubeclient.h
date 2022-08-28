#ifndef INNERTUBECLIENT_H
#define INNERTUBECLIENT_H
#include "CurlEasy.h"
#include "innertubeconfiginfo.h"
#include <QEventLoop>

class InnertubeClient
{
public:
    QString browserName, browserVersion, clientFormFactor, clientName, clientVersion, deviceMake, deviceModel, gl, hl, originalUrl, osName, osVersion,
        platform, remoteHost, timeZone, userAgent, userInterfaceTheme, visitorData;
    InnertubeConfigInfo configInfo;
    int screenDensityFloat, screenPixelDensity;

    InnertubeClient() {}
    InnertubeClient(const QString& clientName, const QString& clientVersion, const QString& platform, const QString& userInterfaceTheme,
                    const QString& browserName = "Firefox", const QString& browserVersion = "103.0", const QString& clientFormFactor = "UNKNOWN_FORM_FACTOR",
                    const InnertubeConfigInfo& configInfo = InnertubeConfigInfo(), const QString& deviceMake = "", const QString& deviceModel = "",
                    const QString& gl = "US", const QString& hl = "en", const QString& originalUrl = "", const QString& osName = "",
                    const QString& osVersion = "", const QString& remoteHost = "", int screenDensityFloat = 2, int screenPixelDensity = 2,
                    const QString& timeZone = "", const QString& userAgent = "")
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

    QJsonObject toJson() const
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
};

#endif // INNERTUBECLIENT_H
