#pragma once
#include "innertube/objects/innertubestring.h"

namespace InnertubeObjects
{
    struct ThumbnailOverlayInlineUnplayable
    {
        QString iconType;
        InnertubeString text;

        ThumbnailOverlayInlineUnplayable() = default;
        explicit ThumbnailOverlayInlineUnplayable(const QJsonValue& thumbnailOverlayInlineUnplayableRenderer)
            : iconType(thumbnailOverlayInlineUnplayableRenderer["icon"]["iconType"].toString()),
              text(thumbnailOverlayInlineUnplayableRenderer["text"]) {}
    };
}
