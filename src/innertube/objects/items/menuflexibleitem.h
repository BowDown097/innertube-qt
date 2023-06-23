#ifndef MENUFLEXIBLEITEM_H
#define MENUFLEXIBLEITEM_H
#include "button.h"
#include "menuserviceitem.h"

namespace InnertubeObjects
{
    class MenuFlexibleItem
    {
    public:
        MenuServiceItem menuItem;
        Button topLevelButton;

        MenuFlexibleItem() = default;
        explicit MenuFlexibleItem(const QJsonValue& menuFlexibleItemRenderer)
            : menuItem(menuFlexibleItemRenderer["menuItem"]["menuServiceItemRenderer"]),
              topLevelButton(menuFlexibleItemRenderer["topLevelButton"]["buttonRenderer"]) {}
    };
}

#endif // MENUFLEXIBLEITEM_H
