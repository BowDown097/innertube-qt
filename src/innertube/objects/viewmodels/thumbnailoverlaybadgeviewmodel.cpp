#include "thumbnailoverlaybadgeviewmodel.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    ThumbnailOverlayBadgeViewModel::ThumbnailOverlayBadgeViewModel(const QJsonValue& thumbnailOverlayBadgeViewModel)
        : position(thumbnailOverlayBadgeViewModel["position"].toString())
    {
        const QJsonArray thumbnailBadgesJson = thumbnailOverlayBadgeViewModel["thumbnailBadges"].toArray();
        for (const QJsonValue& thumbnailBadge : thumbnailBadgesJson)
            thumbnailBadges.append(InnertubeObjects::ThumbnailBadgeViewModel(thumbnailBadge["thumbnailBadgeViewModel"]));
    }
}
