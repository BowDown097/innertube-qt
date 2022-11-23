#include "videosecondaryinfo.h"
#include <QJsonArray>
#include <QJsonObject>

namespace InnertubeObjects
{
    VideoSecondaryInfo::VideoSecondaryInfo(const QJsonValue& secondaryInfoRenderer)
        : channelId(secondaryInfoRenderer["subscribeButton"]["subscribeButtonRenderer"]["channelId"].toString()),
          channelName(secondaryInfoRenderer["owner"]["videoOwnerRenderer"]["title"]),
          description(secondaryInfoRenderer["description"]),
          subscribed(secondaryInfoRenderer["subscribeButton"]["subscribeButtonRenderer"]["subscribed"].toBool()),
          subscriberCountText(secondaryInfoRenderer["owner"]["videoOwnerRenderer"]["subscriberCountText"]),
          subscriptionsEnabled(secondaryInfoRenderer["subscribeButton"]["subscribeButtonRenderer"]["enabled"].toBool()),
          subscriptionType(secondaryInfoRenderer["subscribeButton"]["subscribeButtonRenderer"]["type"].toString())
    {
        const QJsonArray thumbnails = secondaryInfoRenderer["owner"]["videoOwnerRenderer"]["thumbnail"]["thumbnails"].toArray();
        for (const QJsonValue& v : thumbnails)
            channelIcons.append(GenericThumbnail(v["height"].toInt(), v["url"].toString(), v["width"].toInt()));
    }
}
