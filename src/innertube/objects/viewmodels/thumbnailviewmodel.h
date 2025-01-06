#pragma once
#include "innertube/objects/images/responsiveimage.h"
#include "innertube/objects/viewmodels/thumbnailbottomoverlayviewmodel.h"
#include "innertube/objects/viewmodels/thumbnailhoveroverlaytoggleactionsviewmodel.h"
#include "innertube/objects/viewmodels/thumbnailoverlaybadgeviewmodel.h"

namespace InnertubeObjects
{
    struct ThumbnailViewModel
    {
        ResponsiveImage image;
        QList<std::variant<
            InnertubeObjects::ThumbnailBottomOverlayViewModel,
            InnertubeObjects::ThumbnailHoverOverlayToggleActionsViewModel,
            InnertubeObjects::ThumbnailOverlayBadgeViewModel>> overlays;

        ThumbnailViewModel() = default;
        explicit ThumbnailViewModel(const QJsonValue& thumbnailViewModel);
    };
}
