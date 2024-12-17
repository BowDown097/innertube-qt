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
            auto begin = overlay.toObject().constBegin();
            if (begin.key() == "thumbnailOverlayBadgeViewModel")
                overlays.append(InnertubeObjects::ThumbnailOverlayBadgeViewModel(begin.value()));
            else if (begin.key() == "thumbnailHoverOverlayToggleActionsViewModel")
                overlays.append(InnertubeObjects::ThumbnailHoverOverlayToggleActionsViewModel(begin.value()));
        }
    }
}
