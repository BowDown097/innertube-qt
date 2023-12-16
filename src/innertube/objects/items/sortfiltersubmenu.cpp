#include "sortfiltersubmenu.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    SortFilterSubMenu::SortFilterSubMenu(const QJsonValue& sortFilterSubMenuRenderer)
        : accessibilityLabel(sortFilterSubMenuRenderer["accessibility"]["accessibilityData"]["label"].toString()),
          iconType(sortFilterSubMenuRenderer["icon"]["iconType"].toString()),
          title(sortFilterSubMenuRenderer["title"].toString()),
          tooltip(sortFilterSubMenuRenderer["tooltip"].toString())
    {
        const QJsonArray subMenuItemsJson = sortFilterSubMenuRenderer["subMenuItems"].toArray();
        for (const QJsonValue& subMenuItem : subMenuItemsJson)
            subMenuItems.append(MenuServiceItem(subMenuItem));
    }
}
