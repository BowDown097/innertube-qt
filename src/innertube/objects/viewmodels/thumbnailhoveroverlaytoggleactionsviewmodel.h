#pragma once
#include "togglebuttonviewmodel.h"

namespace InnertubeObjects
{
    struct ThumbnailHoverOverlayToggleActionsViewModel
    {
        QList<ToggleButtonViewModel> buttons;

        ThumbnailHoverOverlayToggleActionsViewModel() = default;
        explicit ThumbnailHoverOverlayToggleActionsViewModel(const QJsonValue& thumbnailHoverOverlayToggleActionsViewModel);
    };
}
