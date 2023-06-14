#ifndef CHANNEL_H
#define CHANNEL_H
#include "innertube/objects/genericthumbnail.h"
#include "innertube/objects/innertubestring.h"
#include "subscribebutton.h"

namespace InnertubeObjects
{
    class Channel
    {
    public:
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
