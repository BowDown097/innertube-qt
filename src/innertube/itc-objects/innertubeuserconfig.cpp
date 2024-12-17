#include "innertubeuserconfig.h"
#include <QJsonObject>

QJsonObject InnertubeUserConfig::toJson() const
{
    return {
        { "lockedSafetyMode", lockedSafetyMode }
    };
}
