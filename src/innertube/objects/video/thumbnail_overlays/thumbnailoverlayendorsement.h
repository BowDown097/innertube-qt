#pragma once
#include "innertube/objects/innertubestring.h"

namespace InnertubeObjects
{
    struct ThumbnailOverlayEndorsement
    {
        InnertubeString text;

        ThumbnailOverlayEndorsement() = default;
        explicit ThumbnailOverlayEndorsement(const QJsonValue& thumbnailOverlayEndorsementRenderer)
            : text(thumbnailOverlayEndorsementRenderer["text"]) {}
    };
}
