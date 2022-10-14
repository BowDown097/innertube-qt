#ifndef INNERTUBECLIENT_H
#define INNERTUBECLIENT_H
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
                    const QString& timeZone = "", const QString& userAgent = "");
    QJsonObject toJson() const;
};

#endif // INNERTUBECLIENT_H
