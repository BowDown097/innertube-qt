#include "channel.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    Channel::Channel(const QJsonValue& channelRenderer)
        : channelId(channelRenderer["channelId"].toString()),
          descriptionSnippet(InnertubeString(channelRenderer["descriptionSnippet"])),
          subscribed(channelRenderer["subscriptionButton"]["subscribed"].toBool()),
          subscriberCountText(InnertubeString(channelRenderer["subscriberCountText"])), title(InnertubeString(channelRenderer["title"])),
          videoCountText(InnertubeString(channelRenderer["videoCountText"]))
    {
        const QJsonArray thumbnailsJson = channelRenderer["thumbnail"]["thumbnails"].toArray();
        for (const QJsonValue& v : thumbnailsJson)
            thumbnails.append(GenericThumbnail(v["height"].toInt(), "https:" + v["url"].toString(), v["width"].toInt()));
    }
}
