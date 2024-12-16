#pragma once
#include "innertube/objects/images/responsiveimage.h"

namespace InnertubeObjects
{
    struct ThumbnailViewModel
    {
        ResponsiveImage image;
        QJsonValue overlays;

        ThumbnailViewModel() = default;
        explicit ThumbnailViewModel(const QJsonValue& thumbnailViewModel)
            : image(thumbnailViewModel["image"]["sources"]),
              overlays(thumbnailViewModel["overlays"]) {}
    };
}
