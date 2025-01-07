#include "thumbnailviewmodel.h"
#include <QJsonArray>
#include <QJsonObject>

namespace InnertubeObjects
{
    ThumbnailViewModel::ThumbnailViewModel(const QJsonValue& thumbnailViewModel)
        : image(thumbnailViewModel["image"]["sources"])
    {
        const QJsonArray overlaysJson = thumbnailViewModel["overlays"].toArray();
        for (const QJsonValue& overlay : overlaysJson)
        {
            if (const QJsonValue bottom = overlay["thumbnailBottomOverlayViewModel"]; bottom.isObject())
                overlays.append(ThumbnailBottomOverlayViewModel(bottom));
            else if (const QJsonValue hover = overlay["thumbnailHoverOverlayToggleActionsViewModel"]; hover.isObject())
                overlays.append(ThumbnailHoverOverlayToggleActionsViewModel(hover));
            else if (const QJsonValue badge = overlay["thumbnailOverlayBadgeViewModel"]; badge.isObject())
                overlays.append(ThumbnailOverlayBadgeViewModel(badge));
        }
    }
}
