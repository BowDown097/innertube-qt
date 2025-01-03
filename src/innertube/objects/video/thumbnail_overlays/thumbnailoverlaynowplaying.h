#pragma once
#include "innertube/objects/innertubestring.h"

namespace InnertubeObjects
{
    struct ThumbnailOverlayNowPlaying
    {
        InnertubeString text;

        ThumbnailOverlayNowPlaying() = default;
        explicit ThumbnailOverlayNowPlaying(const QJsonValue& thumbnailOverlayNowPlayingRenderer)
            : text(thumbnailOverlayNowPlayingRenderer["text"]) {}
    };
}
