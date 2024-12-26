#pragma once
#include "innertube/objects/items/menu/menu.h"
#include "innertube/objects/viewmodels/shortslockupviewmodel.h"

namespace InnertubeObjects
{
    struct ReelShelf
    {
        Menu button;
        QString icon;
        QList<ShortsLockupViewModel> items;
        InnertubeString title;

        explicit ReelShelf(const QJsonValue& reelShelfRenderer);
    };
}
