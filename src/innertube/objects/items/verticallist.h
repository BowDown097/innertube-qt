#pragma once
#include "innertube/objects/innertubestring.h"
#include <QJsonArray>
#include <span>

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
    class VerticalList : public VerticalListBase
    {
    public:
        QList<std::variant<ItemTypes...>> items;
        VerticalList(const QJsonValue& verticalListRenderer, const std::array<QString, sizeof...(ItemTypes)>& itemKeys)
            : VerticalListBase(verticalListRenderer)
        {
            std::span keysSpan(itemKeys);
            const QJsonArray itemsArr = verticalListRenderer["items"].toArray();
            for (auto it = itemsArr.begin(); it != itemsArr.end(); ++it)
            {
                [this, it, keysSpan]<size_t... Is>(std::index_sequence<Is...>) {
                    (tryCreateInstance<Is>(it, keysSpan), ...);
                }(std::index_sequence_for<ItemTypes...>());
            }
        }
    private:
        template<size_t I>
        void tryCreateInstance(auto it, std::span<const QString> keys)
        {
            using ItemType = std::tuple_element_t<I, std::tuple<ItemTypes...>>;
            if (const QJsonValue subItem = (*it)[keys[I]]; subItem.isObject())
                items.append(ItemType(subItem));
        }
    };

    template<typename T>
    struct VerticalList<T> : VerticalListBase
    {
        QList<T> items;
        VerticalList(const QJsonValue& verticalListRenderer, const QString& itemKey)
            : VerticalListBase(verticalListRenderer)
        {
            const QJsonArray itemsArr = verticalListRenderer["items"].toArray();
            for (const QJsonValue& item : itemsArr)
                if (const QJsonValue subItem = item[itemKey]; subItem.isObject())
                    items.append(T(subItem));
        }
    };
}
