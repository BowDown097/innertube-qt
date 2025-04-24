#pragma once
#include "innertube/objects/ad/adslot.h"
#include "innertube/objects/video/compactvideo.h"
#include "relatedchipcloud.h"

namespace InnertubeObjects
{
    using WatchNextFeedItem = std::variant<AdSlot, CompactVideo>;

    struct WatchNextSecondaryResults
    {
        QList<WatchNextFeedItem> feed;
        QString feedContinuation;
        std::optional<RelatedChipCloud> relatedChipCloud;

        WatchNextSecondaryResults() = default;
        explicit WatchNextSecondaryResults(const QJsonValue& results);
    };
}
