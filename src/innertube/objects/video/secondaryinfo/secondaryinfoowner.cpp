#include "secondaryinfoowner.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    SecondaryInfoOwner::SecondaryInfoOwner(const QJsonValue& videoOwnerRenderer)
        : navigationEndpoint(videoOwnerRenderer["navigationEndpoint"]),
          subscriberCountText(videoOwnerRenderer["subscriberCountText"]),
          subscriptionType(videoOwnerRenderer["subscriptionButton"]["type"].toString()),
          title(videoOwnerRenderer["title"])
    {
        const QJsonArray badgesJson = videoOwnerRenderer["badges"].toArray();
        for (const QJsonValue& v : badgesJson)
            badges.append(MetadataBadge(v["metadataBadgeRenderer"]));

        const QJsonArray thumbnailsJson = videoOwnerRenderer["thumbnail"]["thumbnails"].toArray();
        for (const QJsonValue& v : thumbnailsJson)
            thumbnails.append(GenericThumbnail(v));
    }
}
