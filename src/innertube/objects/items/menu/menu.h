#ifndef MENU_H
#define MENU_H
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

#endif // MENU_H
