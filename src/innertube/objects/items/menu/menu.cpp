#include "menu.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    Menu::Menu(const QJsonValue& menuRenderer)
        : accessibilityLabel(menuRenderer["accessibility"]["accessibilityData"]["label"].toString()),
          menuPopupAccessibilityLabel(menuRenderer["menuPopupAccessibility"]["label"].toString())
    {
        const QJsonArray itemsJson = menuRenderer["items"].toArray();
        for (const QJsonValue& item : itemsJson)
            items.append(MenuServiceItem(item["menuServiceItemRenderer"]));
    }
}
