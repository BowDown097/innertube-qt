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
          subscriberCountText(channelRenderer["subscriberCountText"]),
          subscriptionButton(channelRenderer["subscriptionButton"]),
          thumbnail(channelRenderer["thumbnail"]["thumbnails"]),
          title(channelRenderer["title"]),
          videoCountText(channelRenderer["videoCountText"])
    {
        if (const QJsonValue subscribeButtonRenderer = channelRenderer["subscribeButton"]["subscribeButtonRenderer"];
            subscribeButtonRenderer.isObject())
        {
            subscribeButton = SubscribeButton(subscribeButtonRenderer);
        }
        else
        {
            subscribeButton = Button(channelRenderer["subscribeButton"]["buttonRenderer"]);
        }

        const QJsonArray ownerBadgesArr = channelRenderer["ownerBadges"].toArray();
        for (const QJsonValue& ownerBadge : ownerBadgesArr)
            ownerBadges.append(MetadataBadge(ownerBadge["metadataBadgeRenderer"]));
    }
}
