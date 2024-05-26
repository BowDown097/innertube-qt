#include "channel.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    Channel::Channel(const QJsonValue& channelRenderer)
        : channelId(channelRenderer["channelId"].toString()),
          descriptionSnippet(channelRenderer["descriptionSnippet"]),
          longBylineText(channelRenderer["longBylineText"]),
          navigationEndpoint(channelRenderer["navigationEndpoint"]),
          shortBylineText(channelRenderer["shortBylineText"]),
          subscribeButton(channelRenderer["subscribeButton"]["subscribeButtonRenderer"]),
          subscribed(channelRenderer["subscriptionButton"]["subscribed"].toBool()),
          subscriberCountText(channelRenderer["subscriberCountText"]),
          thumbnail(channelRenderer["thumbnail"]["thumbnails"]),
          title(channelRenderer["title"]),
          videoCountText(channelRenderer["videoCountText"])
    {
        const QJsonArray ownerBadgesArr = channelRenderer["ownerBadges"].toArray();
        for (const QJsonValue& ownerBadge : ownerBadgesArr)
            ownerBadges.append(MetadataBadge(ownerBadge["metadataBadgeRenderer"]));
    }
}
