#ifndef INNERTUBECLIENT_H
#define INNERTUBECLIENT_H
#include "innertubeconfiginfo.h"

class InnertubeClient
{
public:
    // courtesy of https://github.com/zerodytrash/YouTube-Internal-Clients
    enum class ClientType
    {
        WEB = 1,
        MWEB = 2,
        ANDROID = 3,
        IOS = 5,
        TVHTML5 = 7,
        TVLITE = 8,
        TVANDROID = 10,
        XBOXONEGUIDE = 13,
        ANDROID_CREATOR = 14,
        IOS_CREATOR = 15,
        TVAPPLE = 16,
        ANDROID_KIDS = 18,
        IOS_KIDS = 19,
        ANDROID_MUSIC = 21,
        ANDROID_TV = 23,
        IOS_MUSIC = 26,
        MWEB_TIER_2 = 27,
        ANDROID_VR = 28,
        ANDROID_UNPLUGGED = 29,
        ANDROID_TESTSUITE = 30,
        WEB_MUSIC_ANALYTICS = 31,
        IOS_UNPLUGGED = 33,
        ANDROID_LITE = 38,
        IOS_EMBEDDED_PLAYER = 39,
        WEB_UNPLUGGED = 41,
        WEB_EXPERIMENTS = 42,
        TVHTML5_CAST = 43,
        ANDROID_EMBEDDED_PLAYER = 55,
        WEB_EMBEDDED_PLAYER = 56,
        TVHTML5_AUDIO = 57,
        TV_UNPLUGGED_CAST = 58,
        TVHTML5_KIDS = 59,
        WEB_HEROES = 60,
        WEB_MUSIC = 61,
        WEB_CREATOR = 62,
        TV_UNPLUGGED_ANDROID = 63,
        IOS_LIVE_CREATION_EXTENSION = 64,
        TVHTML5_UNPLUGGED = 65,
        IOS_MESSAGES_EXTENSION = 66,
        WEB_REMIX = 67,
        IOS_UPTIME = 68,
        WEB_UNPLUGGED_ONBOARDING = 69,
        WEB_UNPLUGGED_OPS = 70,
        WEB_UNPLUGGED_PUBLIC = 71,
        TVHTML5_VR = 72,
        ANDROID_TV_KIDS = 74,
        TVHTML5_SIMPLY = 75,
        WEB_KIDS = 76,
        MUSIC_INTEGRATIONS = 77,
        TVHTML5_YONGLE = 80,
        GOOGLE_ASSISTANT = 84,
        TVHTML5_SIMPLY_EMBEDDED_PLAYER = 85,
        WEB_INTERNAL_ANALYTICS = 87,
        WEB_PARENT_TOOLS = 88,
        GOOGLE_MEDIA_ACTIONS = 89,
        WEB_PHONE_VERIFICATION = 90,
        IOS_PRODUCER = 92,
        TVHTML5_FOR_KIDS = 93,
        GOOGLE_LIST_RECS = 94,
        MEDIA_CONNECT_FRONTEND = 95
    };

    QString browserName;
    QString browserVersion;
    QString clientFormFactor;
    ClientType clientType;
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
    InnertubeClient(const ClientType& clientType, const QString& clientVersion, const QString& platform,
                    const QString& userAgent = "", const QString& browserName = "Firefox",
                    const QString& browserVersion = "103.0", const QString& userInterfaceTheme = "USER_INTERFACE_THEME_DARK",
                    const QString& clientFormFactor = "UNKNOWN_FORM_FACTOR", const InnertubeConfigInfo& configInfo = InnertubeConfigInfo(),
                    const QString& deviceMake = "", const QString& deviceModel = "", const QString& gl = "US",
                    const QString& hl = "en", const QString& originalUrl = "", const QString& osName = "",
                    const QString& osVersion = "", const QString& remoteHost = "", int screenDensityFloat = 2,
                    int screenPixelDensity = 2, const QString& timeZone = "");
    QJsonObject toJson() const;
};

#endif // INNERTUBECLIENT_H
