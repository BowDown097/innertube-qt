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

    template<typename... ItemTypes>
    struct HorizontalList : HorizontalListBase, ListBase<ItemTypes...>
    {
        HorizontalList(const QJsonValue& horizontalListRenderer, const std::array<QString, sizeof...(ItemTypes)>& itemKeys)
            : HorizontalListBase(horizontalListRenderer), ListBase<ItemTypes...>(horizontalListRenderer, itemKeys) {}
    };

    template<typename T>
    struct HorizontalList<T> : HorizontalListBase, ListBase<T>
    {
        HorizontalList(const QJsonValue& horizontalListRenderer, const QString& itemKey)
            : HorizontalListBase(horizontalListRenderer), ListBase<T>(horizontalListRenderer, itemKey) {}
    };
}
