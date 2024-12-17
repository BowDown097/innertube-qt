#include "innertubeconfiginfo.h"
#include <QJsonObject>

QJsonObject InnertubeConfigInfo::toJson() const
{
    return {
        { "appInstallData", appInstallData }
    };
}
