#ifndef INNERTUBECLIENT_H
#define INNERTUBECLIENT_H
#include "innertubeconfiginfo.h"

class InnertubeClient
{
public:
    QString browserName, browserVersion, clientFormFactor, clientName, clientVersion, deviceMake, deviceModel, gl, hl, originalUrl, osName, osVersion,
        platform, remoteHost, timeZone, userAgent, userInterfaceTheme, visitorData;
    InnertubeConfigInfo configInfo;
    int screenDensityFloat, screenPixelDensity;

    InnertubeClient() {}
    InnertubeClient(const QString& cliName, const QString& cliVer, const QString& plat, const QString& theme, const QString& visitor = "",
                    const QString& bName = "Firefox", const QString& bVer = "103.0", const QString& cFF = "UNKNOWN_FORM_FACTOR",
                    const InnertubeConfigInfo& cI = InnertubeConfigInfo(), const QString& dMake = "", const QString& dModel = "", const QString& _gl = "US",
                    const QString& _hl = "en", const QString& origUrl = "", const QString& _osName = "", const QString& osVer = "", const QString& rHost = "",
                    int sDF = 2, int sPD = 2, const QString& tz = "", const QString& agent = "")
        : browserName(bName), browserVersion(bVer), clientFormFactor(cFF), clientName(cliName), clientVersion(cliVer), deviceMake(dMake),
          deviceModel(dModel), gl(_gl), hl(_hl), originalUrl(origUrl), osName(_osName), osVersion(osVer), platform(plat), remoteHost(rHost), timeZone(tz),
          userAgent(agent), userInterfaceTheme(theme), configInfo(cI), screenDensityFloat(sDF), screenPixelDensity(sPD)
    {
        genVisitorData(visitor);
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

    void genVisitorData(const QString& visitor)
    {
        visitorData = QByteArray("\x0a" + uleb128(visitor.length()) + visitor.toLatin1() + "\x28" + uleb128(time(NULL))).toBase64().toPercentEncoding();
    }
private:
    QByteArray uleb128(uint64_t val)
    {
        uint8_t buf[128];
        size_t i = 0;
        do
        {
            if (i < 255)
            {
                uint8_t b = val & 0x7F;
                val >>= 7;
                if (val != 0)
                    b |= 0x80;
                buf[i++] = b;
            }
            else
            {
                return 0;
            }
        } while (val != 0);

        return QByteArray(reinterpret_cast<char*>(buf), i);
    }
};

#endif // INNERTUBECLIENT_H
