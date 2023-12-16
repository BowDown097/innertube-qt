#ifndef SORTFILTERSUBMENU_H
#define SORTFILTERSUBMENU_H
#include "menu/menuserviceitem.h"

namespace InnertubeObjects
{
    struct SortFilterSubMenu
    {
        QString accessibilityLabel;
        QString iconType;
        QList<MenuServiceItem> subMenuItems;
        QString title;
        QString tooltip;

        SortFilterSubMenu() = default;
        explicit SortFilterSubMenu(const QJsonValue& sortFilterSubMenuRenderer);
    };
}

#endif // SORTFILTERSUBMENU_H
