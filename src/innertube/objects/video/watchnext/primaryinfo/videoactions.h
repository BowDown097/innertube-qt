#pragma once
#include "innertube/objects/items/menu/menuflexibleitem.h"
#include "innertube/objects/items/menu/menuserviceitem.h"
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
