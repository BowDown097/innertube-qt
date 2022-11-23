#ifndef CHANNEL_H
#define CHANNEL_H
#include "innertube/objects/genericthumbnail.h"
#include "innertube/objects/innertubestring.h"
#include <QJsonValue>

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
        explicit Channel(const QJsonValue& channelRenderer);
    };
}

#endif // CHANNEL_H
