#ifndef MENUFLEXIBLEITEM_H
#define MENUFLEXIBLEITEM_H
#include "innertube/objects/viewmodels/buttonviewmodel.h"
#include "menuserviceitem.h"
#include <QJsonObject>

namespace InnertubeObjects
{
    class MenuFlexibleItem
    {
    public:
        MenuServiceItem menuItem;
        ButtonViewModel topLevelButton;

        MenuFlexibleItem() = default;
        explicit MenuFlexibleItem(const QJsonValue& menuFlexibleItemRenderer)
            : menuItem(menuFlexibleItemRenderer["menuItem"].toObject().constBegin().value()),
              topLevelButton(menuFlexibleItemRenderer["topLevelButton"].toObject().constBegin().value()) {}
    };
}

#endif // MENUFLEXIBLEITEM_H
