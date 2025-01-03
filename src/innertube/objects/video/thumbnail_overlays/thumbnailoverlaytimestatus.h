#pragma once
#include "innertube/objects/innertubestring.h"

namespace InnertubeObjects
{
    struct ThumbnailOverlayTimeStatus
    {
        QString style;
        InnertubeString text;

        ThumbnailOverlayTimeStatus() = default;
        explicit ThumbnailOverlayTimeStatus(const QJsonValue& thumbnailOverlayTimeStatusRenderer)
            : style(thumbnailOverlayTimeStatusRenderer["style"].toString()),
              text(thumbnailOverlayTimeStatusRenderer["text"]) {}
    };
}
