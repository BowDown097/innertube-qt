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

            /*
            auto begin = overlay.toObject().constBegin();
            const QString& key = begin.key();
            if (key == "thumbnailBottomOverlayViewModel")
                overlays.append(ThumbnailBottomOverlayViewModel(begin.value()));
            else if (key == "thumbnailHoverOverlayToggleActionsViewModel")
                overlays.append(ThumbnailHoverOverlayToggleActionsViewModel(begin.value()));
            else if (key == "thumbnailOverlayBadgeViewModel")
                overlays.append(ThumbnailOverlayBadgeViewModel(begin.value()));
            */
        }
    }
}
