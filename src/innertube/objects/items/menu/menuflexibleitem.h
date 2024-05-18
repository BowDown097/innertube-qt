#pragma once
#include "innertube/objects/viewmodels/buttonviewmodel.h"
#include "menuserviceitem.h"
#include <QJsonObject>

namespace InnertubeObjects
{
    struct MenuFlexibleItem
    {
        MenuServiceItem menuItem;
        ButtonViewModel topLevelButton;

        MenuFlexibleItem() = default;
        explicit MenuFlexibleItem(const QJsonValue& menuFlexibleItemRenderer)
            : menuItem(menuFlexibleItemRenderer["menuItem"].toObject().constBegin().value()),
              topLevelButton(menuFlexibleItemRenderer["topLevelButton"].toObject().constBegin().value()) {}
    };
}
