#pragma once
#include "thumbnailbadgeviewmodel.h"
#include "thumbnailoverlayprogressbarviewmodel.h"

namespace InnertubeObjects
{
    struct ThumbnailBottomOverlayViewModel
    {
        QList<ThumbnailBadgeViewModel> badges;
        ThumbnailOverlayProgressBarViewModel progressBar;

        ThumbnailBottomOverlayViewModel() = default;
        explicit ThumbnailBottomOverlayViewModel(const QJsonValue& thumbnailBottomOverlayViewModel);
    };
}
