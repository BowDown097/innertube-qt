#include "innertubeconfiginfo.h"
#include <QJsonObject>

QJsonValue InnertubeConfigInfo::toJson() const
{
    return QJsonObject {
        { "appInstallData", appInstallData }
    };
}
