#pragma once
#include "innertube/objects/innertubestring.h"
#include "listbase.h"

namespace InnertubeObjects
{
    struct VerticalListBase
    {
        int collapsedItemCount;
        InnertubeString collapsedStateButtonText;

        explicit VerticalListBase(const QJsonValue& verticalListRenderer)
            : collapsedItemCount(verticalListRenderer["collapsedItemCount"].toInt()),
              collapsedStateButtonText(verticalListRenderer["collapsedStateButtonText"]) {}
    };

    INNERTUBE_CREATE_LIST_CLASS(VerticalList)
}
