#pragma once
#include "menuserviceitem.h"

namespace InnertubeObjects
{
    struct Menu
    {
        QString accessibilityLabel;
        QList<MenuServiceItem> items;
        QString menuPopupAccessibilityLabel;

        Menu() = default;
        explicit Menu(const QJsonValue& menuRenderer);
    };
}
