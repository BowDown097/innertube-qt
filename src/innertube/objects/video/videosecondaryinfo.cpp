#include "videosecondaryinfo.h"
#include <QJsonArray>
#include <QJsonObject>

namespace InnertubeObjects
{
    VideoSecondaryInfo::VideoSecondaryInfo(const QJsonValue& secondaryInfoRenderer) : description(secondaryInfoRenderer["description"])
    {
        QJsonObject videoOwnerRenderer = secondaryInfoRenderer["owner"]["videoOwnerRenderer"].toObject();
        channelName = InnertubeString(videoOwnerRenderer["title"]);
        subscriberCountText = InnertubeString(videoOwnerRenderer["subscriberCountText"]);
        for (auto&& v : videoOwnerRenderer["thumbnail"].toObject()["thumbnails"].toArray())
        {
            QJsonObject o = v.toObject();
            channelIcons.append(GenericThumbnail(o["height"].toInt(), o["url"].toString(), o["width"].toInt()));
        }

        QJsonObject subscribeButtonRenderer = secondaryInfoRenderer["subscribeButton"]["subscribeButtonRenderer"].toObject();
        channelId = subscribeButtonRenderer["channelId"].toString();
        subscribed = subscribeButtonRenderer["subscribed"].toBool();
        subscriptionsEnabled = subscribeButtonRenderer["enabled"].toBool();
        subscriptionType = subscribeButtonRenderer["type"].toString();
    }
}
