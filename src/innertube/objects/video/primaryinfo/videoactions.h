#ifndef VIDEOACTIONS_H
#define VIDEOACTIONS_H
#include "innertube/objects/items/menuflexibleitem.h"
#include "innertube/objects/items/menuserviceitem.h"
#include "likedislike/likedislikeviewmodel.h"

namespace InnertubeObjects
{
    struct VideoActions
    {
        QString accessibilityLabel;
        QList<MenuFlexibleItem> flexibleItems;
        QList<MenuServiceItem> items;
        LikeDislikeViewModel segmentedLikeDislikeButtonViewModel;

        VideoActions() = default;
        explicit VideoActions(const QJsonValue& menuRenderer);
    };
}

#endif // VIDEOACTIONS_H
