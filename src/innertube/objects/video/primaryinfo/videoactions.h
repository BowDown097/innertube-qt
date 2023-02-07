#ifndef VIDEOACTIONS_H
#define VIDEOACTIONS_H
#include "innertube/objects/items/menuflexibleitem.h"
#include "innertube/objects/items/menuserviceitem.h"
#include "innertube/objects/items/togglebutton.h"

namespace InnertubeObjects
{
    class VideoActions
    {
    public:
        QString accessibilityLabel;
        ToggleButton dislikeButton;
        QList<MenuFlexibleItem> flexibleItems;
        QList<MenuServiceItem> items;
        ToggleButton likeButton;
        Button shareButton;

        VideoActions() {}
        explicit VideoActions(const QJsonValue& menuRenderer);
    };
}

#endif // VIDEOACTIONS_H
