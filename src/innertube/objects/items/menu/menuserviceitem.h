#pragma once
#include "innertube/objects/innertubestring.h"

namespace InnertubeObjects
{
    struct MenuServiceItem
    {
        QString iconType;
        bool isDisabled;
        bool selected;
        QJsonValue serviceEndpoint;
        InnertubeString text;

        MenuServiceItem() = default;
        explicit MenuServiceItem(const QJsonValue& menuServiceItemRenderer)
            : iconType(menuServiceItemRenderer["icon"]["iconType"].toString()),
              isDisabled(menuServiceItemRenderer["isDisabled"].toBool()),
              selected(menuServiceItemRenderer["selected"].toBool()),
              serviceEndpoint(menuServiceItemRenderer["serviceEndpoint"]),
              text(menuServiceItemRenderer["text"]) {}
    };
}
