#ifndef CHANNEL_H
#define CHANNEL_H
#include "../genericthumbnail.h"
#include "../innertubestring.h"

namespace InnertubeObjects
{
    class Channel
    {
    public:
        QString channelId;
        InnertubeString descriptionSnippet;
        bool subscribed;
        InnertubeString subscriberCountText;
        QVector<GenericThumbnail> thumbnails;
        InnertubeString title;
        InnertubeString videoCountText;

        explicit Channel(const QJsonObject& channelRenderer) : channelId(channelRenderer["channelId"].toString()),
            descriptionSnippet(InnertubeString(channelRenderer["descriptionSnippet"])),
            subscribed(channelRenderer["subscriptionButton"].toObject()["subscribed"].toBool()),
            subscriberCountText(InnertubeString(channelRenderer["subscriberCountText"])), title(InnertubeString(channelRenderer["title"])),
            videoCountText(InnertubeString(channelRenderer["videoCountText"]))
        {
            for (auto&& v : channelRenderer["thumbnail"].toObject()["thumbnails"].toArray())
            {
                const QJsonObject& o = v.toObject();
                thumbnails.append(GenericThumbnail(o["height"].toInt(), o["url"].toString(), o["width"].toInt()));
            }
        }
    };
}

#endif // CHANNEL_H
