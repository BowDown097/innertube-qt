#pragma once
#include "innertube/objects/images/responsiveimage.h"
#include "innertube/objects/viewmodels/thumbnailbottomoverlayviewmodel.h"
#include "innertube/objects/viewmodels/thumbnailhoveroverlaytoggleactionsviewmodel.h"
#include "innertube/objects/viewmodels/thumbnailoverlaybadgeviewmodel.h"

namespace InnertubeObjects
{
    using ThumbnailViewModelOverlay = std::variant<
        ThumbnailBottomOverlayViewModel,
        ThumbnailHoverOverlayToggleActionsViewModel,
        ThumbnailOverlayBadgeViewModel>;

    struct ThumbnailViewModel
    {
        ResponsiveImage image;
        QList<ThumbnailViewModelOverlay> overlays;

        ThumbnailViewModel() = default;
        explicit ThumbnailViewModel(const QJsonValue& thumbnailViewModel);
    };
}
