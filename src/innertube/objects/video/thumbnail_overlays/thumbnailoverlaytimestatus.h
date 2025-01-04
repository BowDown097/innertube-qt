#pragma once
#include "innertube/objects/innertubestring.h"

namespace InnertubeObjects
{
    struct ThumbnailOverlayTimeStatus
    {
        QString iconType;
        QString style;
        InnertubeString text;
        QString type;

        ThumbnailOverlayTimeStatus() = default;
        explicit ThumbnailOverlayTimeStatus(const QJsonValue& thumbnailOverlayTimeStatusRenderer)
            : iconType(thumbnailOverlayTimeStatusRenderer["icon"]["iconType"].toString()),
              style(thumbnailOverlayTimeStatusRenderer["style"].toString()),
              text(thumbnailOverlayTimeStatusRenderer["text"]),
              type(thumbnailOverlayTimeStatusRenderer["type"].toString()) {}
    };
}
