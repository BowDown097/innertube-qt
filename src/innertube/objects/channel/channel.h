#ifndef CHANNEL_H
#define CHANNEL_H
#include "../genericthumbnail.h"
#include "../innertubestring.h"
#include <QJsonObject>

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
        explicit Channel(const QJsonObject& channelRenderer);
    };
}

#endif // CHANNEL_H
