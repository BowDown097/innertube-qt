#include "channel.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    Channel::Channel(const QJsonObject& channelRenderer) : channelId(channelRenderer["channelId"].toString()),
        descriptionSnippet(InnertubeString(channelRenderer["descriptionSnippet"])),
        subscribed(channelRenderer["subscriptionButton"].toObject()["subscribed"].toBool()),
        subscriberCountText(InnertubeString(channelRenderer["subscriberCountText"])), title(InnertubeString(channelRenderer["title"])),
        videoCountText(InnertubeString(channelRenderer["videoCountText"]))
    {
        for (auto&& v : channelRenderer["thumbnail"].toObject()["thumbnails"].toArray())
        {
            const QJsonObject& o = v.toObject();
            thumbnails.append(GenericThumbnail(o["height"].toInt(), "https:" + o["url"].toString(), o["width"].toInt()));
        }
    }
}
