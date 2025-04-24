#include "videoowner.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    VideoOwner::VideoOwner(const QJsonValue& videoOwnerRenderer)
        : navigationEndpoint(videoOwnerRenderer["navigationEndpoint"]),
          subscriberCountText(videoOwnerRenderer["subscriberCountText"]),
          subscriptionButton(videoOwnerRenderer["subscriptionButton"]),
          thumbnail(videoOwnerRenderer["thumbnail"]["thumbnails"]),
          title(videoOwnerRenderer["title"])
    {
        const QJsonArray badgesJson = videoOwnerRenderer["badges"].toArray();
        for (const QJsonValue& v : badgesJson)
            badges.append(MetadataBadge(v["metadataBadgeRenderer"]));

        if (const QJsonValue membershipButtonJson = videoOwnerRenderer["membershipButton"]; membershipButtonJson.isObject())
            membershipButton.emplace(membershipButtonJson["timedAnimationButtonRenderer"]["buttonRenderer"]["buttonRenderer"]);
    }
}
