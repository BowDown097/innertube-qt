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

    template<typename... ItemTypes>
    struct VerticalList : VerticalListBase, ListBase<ItemTypes...>
    {
        VerticalList(const QJsonValue& verticalListRenderer, const std::array<QString, sizeof...(ItemTypes)>& itemKeys)
            : VerticalListBase(verticalListRenderer), ListBase<ItemTypes...>(verticalListRenderer, itemKeys) {}
    };

    template<typename T>
    struct VerticalList<T> : VerticalListBase, ListBase<T>
    {
        VerticalList(const QJsonValue& verticalListRenderer, const QString& itemKey)
            : VerticalListBase(verticalListRenderer), ListBase<T>(verticalListRenderer, itemKey) {}
    };
}
