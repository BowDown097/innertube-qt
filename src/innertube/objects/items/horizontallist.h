#pragma once
#include "button.h"
#include "listbase.h"

namespace InnertubeObjects
{
    struct HorizontalListBase
    {
        int collapsedItemCount;
        Button nextButton;
        Button previousButton;
        int visibleItemCount;

        explicit HorizontalListBase(const QJsonValue& horizontalListRenderer)
            : collapsedItemCount(horizontalListRenderer["collapsedItemCount"].toInt()),
              nextButton(horizontalListRenderer["nextButton"]["buttonRenderer"]),
              previousButton(horizontalListRenderer["previousButton"]["buttonRenderer"]),
              visibleItemCount(horizontalListRenderer["visibleItemCount"].toInt()) {}
    };

    INNERTUBE_CREATE_LIST_CLASS(HorizontalList)
}
