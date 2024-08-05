#pragma once
#include "innertube/objects/innertubestring.h"

namespace InnertubeObjects
{
    template<typename ContentType>
    struct Shelf
    {
        ContentType content;
        InnertubeString title;

        Shelf(const QJsonValue& shelfRenderer, const ContentType& content)
            : content(content), title(shelfRenderer["title"]) {}

        Shelf(const QJsonValue& shelfRenderer, const QString& contentKey)
            : content(shelfRenderer["content"][contentKey]), title(shelfRenderer["title"]) {}
    };
}
