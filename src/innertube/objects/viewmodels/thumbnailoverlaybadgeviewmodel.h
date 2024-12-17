#pragma once
#include "thumbnailbadgeviewmodel.h"

namespace InnertubeObjects
{
    struct ThumbnailOverlayBadgeViewModel
    {
        QString position;
        QList<ThumbnailBadgeViewModel> thumbnailBadges;

        ThumbnailOverlayBadgeViewModel() = default;
        explicit ThumbnailOverlayBadgeViewModel(const QJsonValue& thumbnailOverlayBadgeViewModel);
    };
}
