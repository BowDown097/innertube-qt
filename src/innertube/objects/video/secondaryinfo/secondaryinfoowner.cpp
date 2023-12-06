#include "secondaryinfoowner.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    SecondaryInfoOwner::SecondaryInfoOwner(const QJsonValue& videoOwnerRenderer)
        : navigationEndpoint(videoOwnerRenderer["navigationEndpoint"]),
          subscriberCountText(videoOwnerRenderer["subscriberCountText"]),
          subscriptionType(videoOwnerRenderer["subscriptionButton"]["type"].toString()),
          thumbnail(videoOwnerRenderer["thumbnail"]["thumbnails"]),
          title(videoOwnerRenderer["title"])
    {
        const QJsonArray badgesJson = videoOwnerRenderer["badges"].toArray();
        for (const QJsonValue& v : badgesJson)
            badges.append(MetadataBadge(v["metadataBadgeRenderer"]));
    }
}
