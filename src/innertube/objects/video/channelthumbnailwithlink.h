#pragma once
#include "innertube/objects/images/responsiveimage.h"

namespace InnertubeObjects
{
    struct ChannelThumbnailWithLink
    {
        QString accessibilityLabel;
        QJsonValue navigationEndpoint;
        ResponsiveImage thumbnail;

        ChannelThumbnailWithLink() = default;
        explicit ChannelThumbnailWithLink(const QJsonValue& channelThumbnailWithLinkRenderer)
            : accessibilityLabel(channelThumbnailWithLinkRenderer["accessibility"]["accessibilityData"]["label"].toString()),
              navigationEndpoint(channelThumbnailWithLinkRenderer["navigationEndpoint"]),
              thumbnail(channelThumbnailWithLinkRenderer["thumbnail"]["thumbnails"]) {}
    };
}
