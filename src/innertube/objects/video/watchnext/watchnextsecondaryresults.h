#pragma once
#include "innertube/objects/video/compactvideo.h"
#include "relatedchipcloud.h"

namespace InnertubeObjects
{
    struct WatchNextSecondaryResults
    {
        QList<CompactVideo> feed;
        QString feedContinuation;
        std::optional<RelatedChipCloud> relatedChipCloud;

        WatchNextSecondaryResults() = default;
        explicit WatchNextSecondaryResults(const QJsonValue& results);
    };
}
