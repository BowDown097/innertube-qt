#pragma once
#include "innertube/objects/ad/adslot.h"
#include "innertube/objects/viewmodels/lockupviewmodel.h"
#include "relatedchipcloud.h"

namespace InnertubeObjects
{
    using WatchNextFeedItem = std::variant<AdSlot, LockupViewModel>;

    struct WatchNextSecondaryResults
    {
        QList<WatchNextFeedItem> feed;
        QString feedContinuation;
        std::optional<RelatedChipCloud> relatedChipCloud;

        WatchNextSecondaryResults() = default;
        explicit WatchNextSecondaryResults(const QJsonValue& results);
    };
}
