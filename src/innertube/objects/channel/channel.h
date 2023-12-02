#ifndef CHANNEL_H
#define CHANNEL_H
#include "innertube/objects/genericthumbnail.h"
#include "subscribebutton.h"

namespace InnertubeObjects
{
    struct Channel
    {
        QString channelId;
        InnertubeString descriptionSnippet;
        SubscribeButton subscribeButton;
        bool subscribed;
        InnertubeString subscriberCountText;
        QList<GenericThumbnail> thumbnails;
        InnertubeString title;
        InnertubeString videoCountText;

        explicit Channel(const QJsonValue& channelRenderer);
    };
}

#endif // CHANNEL_H
