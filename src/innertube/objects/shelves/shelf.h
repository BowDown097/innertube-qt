#pragma once
#include "innertube/objects/channel/metadatabadge.h"
#include "innertube/objects/images/responsiveimage.h"
#include "innertube/objects/innertubestring.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    template<typename ContentType>
    struct Shelf
    {
        QList<MetadataBadge> badges;
        ContentType content;
        QJsonValue endpoint;
        ResponsiveImage thumbnail;
        InnertubeString title;

        Shelf(const QJsonValue& shelfRenderer, ContentType&& content)
            : content(std::forward<ContentType>(content)),
              endpoint(shelfRenderer["endpoint"]),
              thumbnail(shelfRenderer["thumbnail"]["thumbnails"]),
              title(shelfRenderer["title"])
        {
            const QJsonArray badgesArr = shelfRenderer["badges"].toArray();
            for (const QJsonValue& badge : badgesArr)
                badges.append(MetadataBadge(badge["metadataBadgeRenderer"]));
        }

        Shelf(const QJsonValue& shelfRenderer, const QString& contentKey)
            : Shelf(shelfRenderer, ContentType(shelfRenderer["content"][contentKey])) {}
    };
}
