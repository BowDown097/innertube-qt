#include "innertubeclicktracking.h"
#include <QJsonObject>

QJsonObject InnertubeClickTracking::toJson() const
{
    return {
        { "clickTrackingParams", clickTrackingParams }
    };
}
