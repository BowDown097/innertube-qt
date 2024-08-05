#pragma once
#include "innertube/objects/items/menu/menu.h"
#include "innertube/objects/video/reel.h"

namespace InnertubeObjects
{
    struct ReelShelf
    {
        Menu button;
        QString icon;
        QList<Reel> items;
        InnertubeString title;

        explicit ReelShelf(const QJsonValue& reelShelfRenderer);
    };
}
