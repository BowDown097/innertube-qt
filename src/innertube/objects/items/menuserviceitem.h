#ifndef MENUSERVICEITEM_H
#define MENUSERVICEITEM_H
#include "innertube/objects/innertubestring.h"

namespace InnertubeObjects
{
    struct MenuServiceItem
    {
        QString iconType;
        bool isDisabled;
        QJsonValue serviceEndpoint;
        InnertubeString text;

        MenuServiceItem() = default;
        explicit MenuServiceItem(const QJsonValue& menuServiceItemRenderer)
            : iconType(menuServiceItemRenderer["icon"]["iconType"].toString()),
              isDisabled(menuServiceItemRenderer["isDisabled"].toBool()),
              serviceEndpoint(menuServiceItemRenderer["serviceEndpoint"]),
              text(menuServiceItemRenderer["text"]) {}
    };
}

#endif // MENUSERVICEITEM_H
