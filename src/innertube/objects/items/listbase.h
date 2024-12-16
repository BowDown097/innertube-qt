#pragma once
#include <QJsonArray>
#include <span>

#define INNERTUBE_CREATE_LIST_CLASS(TypeName) \
template<typename... ItemTypes> \
struct TypeName : TypeName##Base, ListBase<ItemTypes...> \
{ \
    TypeName(const QJsonValue& listRenderer, const std::array<QString, sizeof...(ItemTypes)>& itemKeys) \
        : TypeName##Base(listRenderer), ListBase<ItemTypes...>(listRenderer, itemKeys) {} \
}; \
template<typename T> \
struct TypeName<T> : TypeName##Base, ListBase<T> \
{ \
    TypeName(const QJsonValue& listRenderer, const QString& itemKey) \
        : TypeName##Base(listRenderer), ListBase<T>(listRenderer, itemKey) {} \
};

namespace InnertubeObjects
{
    template<typename... ItemTypes>
    class ListBase
    {
    public:
        QList<std::variant<ItemTypes...>> items;
        ListBase(const QJsonValue& listRenderer,
                 const std::array<QString, sizeof...(ItemTypes)>& itemKeys,
                 const QString& itemsKey = "items")
        {
            std::span keysSpan(itemKeys);
            const QJsonArray itemsArr = listRenderer[itemsKey].toArray();
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
