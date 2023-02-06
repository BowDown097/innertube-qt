#include "secondaryinfoowner.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    SecondaryInfoOwner::SecondaryInfoOwner(const QJsonValue& videoOwnerRenderer)
        : subscriberCountText(videoOwnerRenderer["subscriberCountText"]),
          subscriptionType(videoOwnerRenderer["subscriptionButton"]["type"].toString()),
          title(videoOwnerRenderer["title"])
    {
        const QJsonArray thumbnailsJson = videoOwnerRenderer["thumbnail"]["thumbnails"].toArray();
        for (const QJsonValue& v : thumbnailsJson)
            thumbnails.append(GenericThumbnail(v));
    }
}
