#pragma once
#include "basevideo.h"
#include "innertube/objects/channel/metadatabadge.h"
#include "innertube/objects/images/movingthumbnail.h"
#include "videoowner.h"

namespace InnertubeObjects
{
    struct CompactVideo : BaseVideo
    {
        QString accessibilityLabel;
        QList<MetadataBadge> badges;
        ResponsiveImage channelThumbnail;
        QList<MetadataBadge> ownerBadges;
        InnertubeString publishedTimeText;
        MovingThumbnail richThumbnail;
        InnertubeString shortViewCountText;
        InnertubeString viewCountText;

        CompactVideo() = default;
        explicit CompactVideo(const QJsonValue& compactVideoRenderer);

        VideoOwner owner() const;
    };
}
