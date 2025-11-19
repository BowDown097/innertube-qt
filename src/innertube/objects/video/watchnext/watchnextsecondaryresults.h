#pragma once
#include "innertube/objects/ad/adslot.h"
#include "innertube/objects/viewmodels/lockupviewmodel.h"
#include "relatedchipcloud.h"
#include <QJsonObject>

namespace InnertubeObjects
{
    using WatchNextFeedItem = std::variant<AdSlot, LockupViewModel>;

    class WatchNextSecondaryResults
    {
    public:
        QList<WatchNextFeedItem> feed;
        QString feedContinuation;
        std::optional<RelatedChipCloud> relatedChipCloud;

        WatchNextSecondaryResults() = default;
        explicit WatchNextSecondaryResults(const QJsonValue& results);
    private:
        void handleItem(QJsonObject::const_iterator item);
    };
}
