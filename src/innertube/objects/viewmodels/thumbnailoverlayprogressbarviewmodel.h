#pragma once
#include <QJsonValue>

namespace InnertubeObjects
{
    struct ThumbnailOverlayProgressBarViewModel
    {
        int startPercent{};

        ThumbnailOverlayProgressBarViewModel() = default;
        explicit ThumbnailOverlayProgressBarViewModel(const QJsonValue& thumbnailOverlayProgressBarViewModel)
            : startPercent(thumbnailOverlayProgressBarViewModel["startPercent"].toInt()) {}
    };
}
