#pragma once
#include <QJsonValue>

namespace InnertubeObjects
{
    struct ThumbnailOverlayResumePlayback
    {
        int percentDurationWatched{};

        ThumbnailOverlayResumePlayback() = default;
        explicit ThumbnailOverlayResumePlayback(const QJsonValue& thumbnailOverlayResumePlaybackRenderer)
            : percentDurationWatched(thumbnailOverlayResumePlaybackRenderer["percentDurationWatched"].toInt()) {}
    };
}
