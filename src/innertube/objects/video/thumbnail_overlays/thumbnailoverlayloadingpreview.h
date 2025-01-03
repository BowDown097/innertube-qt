#pragma once
#include "innertube/objects/innertubestring.h"

namespace InnertubeObjects
{
    struct ThumbnailOverlayLoadingPreview
    {
        InnertubeString text;

        ThumbnailOverlayLoadingPreview() = default;
        explicit ThumbnailOverlayLoadingPreview(const QJsonValue& thumbnailOverlayLoadingPreviewRenderer)
            : text(thumbnailOverlayLoadingPreviewRenderer["text"].toString()) {}
    };
}
