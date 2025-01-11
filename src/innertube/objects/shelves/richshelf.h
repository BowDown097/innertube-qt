#pragma once
#include "innertube/objects/images/responsiveimage.h"
#include "innertube/objects/items/button.h"
#include "innertube/objects/items/menu/menu.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    struct ResponsiveContainerConfiguration
    {
        bool enableContentSpecificAspectRatio;
        explicit ResponsiveContainerConfiguration(const QJsonValue& responsiveContainerConfiguration)
            : enableContentSpecificAspectRatio(
                  responsiveContainerConfiguration["enableContentSpecificAspectRatio"].toBool()) {}
    };

    struct RichShelfBase
    {
        QString iconType;
        bool isBottomDividerHidden;
        bool isExpanded;
        bool isTopDividerHidden;
        std::optional<Menu> menu;
        ResponsiveContainerConfiguration responsiveContainerConfiguration;
        Button showLessButton;
        Button showMoreButton;
        InnertubeString subtitle;
        ResponsiveImage thumbnail;
        InnertubeString title;

        explicit RichShelfBase(const QJsonValue& richShelfRenderer)
            : iconType(richShelfRenderer["icon"]["iconType"].toString()),
              isBottomDividerHidden(richShelfRenderer["isBottomDividerHidden"].toBool()),
              isExpanded(richShelfRenderer["isExpanded"].toBool()),
              isTopDividerHidden(richShelfRenderer["isTopDividerHidden"].toBool()),
              responsiveContainerConfiguration(richShelfRenderer["responsiveContainerConfiguration"]),
              showLessButton(richShelfRenderer["showLessButton"]["buttonRenderer"]),
              showMoreButton(richShelfRenderer["showMoreButton"]["buttonRenderer"]),
              subtitle(richShelfRenderer["subtitle"]),
              thumbnail(richShelfRenderer["thumbnail"]["thumbnails"]),
              title(richShelfRenderer["title"])
        {
            if (const QJsonValue menuRenderer = richShelfRenderer["menu"]["menuRenderer"]; menuRenderer.isObject())
                menu.emplace(menuRenderer);
        }
    };

    template<typename... ItemTypes>
    class RichShelf : public RichShelfBase
    {
    public:
        QList<std::variant<ItemTypes...>> contents;
        RichShelf(const QJsonValue& richShelfRenderer, const std::array<QString, sizeof...(ItemTypes)>& itemKeys)
            : RichShelfBase(richShelfRenderer)
        {
            std::span keysSpan(itemKeys);
            const QJsonArray contentsArr = richShelfRenderer["contents"].toArray();
            contents.reserve(contentsArr.size());

            for (auto it = contentsArr.begin(); it != contentsArr.end(); ++it)
            {
                [this, it, keysSpan]<size_t... Is>(std::index_sequence<Is...>) {
                    (tryCreateInstance<Is>(*it, keysSpan), ...);
                }(std::index_sequence_for<ItemTypes...>());
            }
        }
    private:
        template<size_t I>
        void tryCreateInstance(const QJsonValue& val, std::span<const QString> keys)
        {
            using ItemType = std::tuple_element_t<I, std::tuple<ItemTypes...>>;
            if (const QJsonValue subItem = val["richItemRenderer"]["content"][keys[I]];
                !subItem.isUndefined() && !subItem.isNull())
            {
                contents.append(ItemType(subItem));
            }
        }
    };

    template<typename T>
    struct RichShelf<T> : RichShelfBase
    {
        QList<T> contents;
        RichShelf(const QJsonValue& richShelfRenderer, const QString& itemKey)
            : RichShelfBase(richShelfRenderer)
        {
            const QJsonArray contentsArr = richShelfRenderer["contents"].toArray();
            contents.reserve(contentsArr.size());

            for (const QJsonValue& item : contentsArr)
            {
                if (const QJsonValue subItem = item["richItemRenderer"]["content"][itemKey];
                    !subItem.isUndefined() && !subItem.isNull())
                {
                    contents.append(T(subItem));
                }
            }
        }
    };
}
