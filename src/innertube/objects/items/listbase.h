#pragma once
#include <QJsonArray>
#include <span>

namespace InnertubeObjects
{
    template<typename... ItemTypes>
    class ListBase
    {
    public:
        QList<std::variant<ItemTypes...>> items;
        ListBase(const QJsonValue& listRenderer, const std::array<QString, sizeof...(ItemTypes)>& itemKeys)
        {
            std::span keysSpan(itemKeys);
            const QJsonArray itemsArr = listRenderer["items"].toArray();
            items.reserve(itemsArr.size());

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
            if (const QJsonValue subItem = (*it)[keys[I]]; !subItem.isUndefined() && !subItem.isNull())
                items.append(ItemType(subItem));
        }
    };

    template<typename T>
    struct ListBase<T>
    {
        QList<T> items;
        ListBase(const QJsonValue& listRenderer, const QString& itemKey)
        {
            const QJsonArray itemsArr = listRenderer["items"].toArray();
            items.reserve(itemsArr.size());

            for (const QJsonValue& item : itemsArr)
                if (const QJsonValue subItem = item[itemKey]; !subItem.isUndefined() && !subItem.isNull())
                    items.append(T(subItem));
        }
    };
}
