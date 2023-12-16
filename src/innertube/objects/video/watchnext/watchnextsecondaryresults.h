#ifndef WATCHNEXTSECONDARYRESULTS_H
#define WATCHNEXTSECONDARYRESULTS_H
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

#endif // WATCHNEXTSECONDARYRESULTS_H
