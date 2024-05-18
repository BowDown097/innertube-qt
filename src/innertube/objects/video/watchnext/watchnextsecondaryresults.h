#pragma once
#include "innertube/objects/video/video.h"
#include "relatedchipcloud.h"

namespace InnertubeObjects
{
    struct WatchNextSecondaryResults
    {
        QList<Video> feed;
        std::optional<QString> feedContinuation;
        std::optional<RelatedChipCloud> relatedChipCloud;

        WatchNextSecondaryResults() = default;
        WatchNextSecondaryResults(const QJsonValue& results);
    };
}
