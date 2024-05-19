#include "innertubeuserconfig.h"
#include <QJsonObject>

QJsonValue InnertubeUserConfig::toJson() const
{
    return QJsonObject {
        { "lockedSafetyMode", lockedSafetyMode }
    };
}
