#ifndef INNERTUBECLIENT_H
#define INNERTUBECLIENT_H
#include "innertubeconfiginfo.h"
#include <QEventLoop>

class InnertubeClient
{
public:
    QString browserName;
    QString browserVersion;
    QString clientFormFactor;
    QString clientName;
    QString clientVersion;
    InnertubeConfigInfo configInfo;
    QString deviceMake;
    QString deviceModel;
    QString gl;
    QString hl;
    QString originalUrl;
    QString osName;
    QString osVersion;
    QString platform;
    QString remoteHost;
    int screenDensityFloat;
    int screenPixelDensity;
    QString timeZone;
    QString userAgent;
    QString userInterfaceTheme;
    QString visitorData;

    InnertubeClient() = default;
    InnertubeClient(const QString& clientName, const QString& clientVersion, const QString& platform, const QString& userAgent = "",
                    const QString& browserName = "Firefox", const QString& browserVersion = "103.0",
                    const QString& userInterfaceTheme = "USER_INTERFACE_THEME_DARK", const QString& clientFormFactor = "UNKNOWN_FORM_FACTOR",
                    const InnertubeConfigInfo& configInfo = InnertubeConfigInfo(), const QString& deviceMake = "", const QString& deviceModel = "",
                    const QString& gl = "US", const QString& hl = "en", const QString& originalUrl = "", const QString& osName = "",
                    const QString& osVersion = "", const QString& remoteHost = "", int screenDensityFloat = 2, int screenPixelDensity = 2,
                    const QString& timeZone = "");
    QJsonObject toJson() const;
};

#endif // INNERTUBECLIENT_H
