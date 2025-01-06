#include "thumbnailbottomoverlayviewmodel.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    ThumbnailBottomOverlayViewModel::ThumbnailBottomOverlayViewModel(const QJsonValue& thumbnailBottomOverlayViewModel)
        : progressBar(thumbnailBottomOverlayViewModel["progressBar"]["thumbnailOverlayProgressBarViewModel"])
    {
        const QJsonArray badgesJson = thumbnailBottomOverlayViewModel["badges"].toArray();
        for (const QJsonValue& badge : badgesJson)
            badges.append(ThumbnailBadgeViewModel(badge["thumbnailBadgeViewModel"]));
    }
}
