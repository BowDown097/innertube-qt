#pragma once
#include "innertube/objects/items/button.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    template<typename ElementType>
    struct RichShelf
    {
        QList<ElementType> contents;
        bool enableContentSpecificAspectRatio;
        bool isBottomDividerHidden;
        bool isExpanded;
        bool isTopDividerHidden;
        Button showLessButton;
        Button showMoreButton;
        InnertubeString title;

        RichShelf(const QJsonValue& richShelfRenderer, std::function<ElementType(const QJsonValue&)> elementFunction)
            : enableContentSpecificAspectRatio(
                  richShelfRenderer["responsiveContainerConfiguration"]["enableContentSpecificAspectRatio"].toBool()),
              isBottomDividerHidden(richShelfRenderer["isBottomDividerHidden"].toBool()),
              isExpanded(richShelfRenderer["isExpanded"].toBool()),
              isTopDividerHidden(richShelfRenderer["isTopDividerHidden"].toBool()),
              showLessButton(richShelfRenderer["showLessButton"]["buttonRenderer"]),
              showMoreButton(richShelfRenderer["showMoreButton"]["buttonRenderer"]),
              title(richShelfRenderer["title"])
        {
            const QJsonArray contentsJson = richShelfRenderer["contents"].toArray();
            for (const QJsonValue& v : contentsJson)
                contents.append(elementFunction(v["richItemRenderer"]["content"]));
        }
    };
}
