#include "innertubeclicktracking.h"
#include <QJsonObject>

QJsonValue InnertubeClickTracking::toJson() const
{
    return QJsonObject {
        { "clickTrackingParams", clickTrackingParams }
    };
}
