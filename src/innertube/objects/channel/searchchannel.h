#ifndef SEARCHCHANNEL_H
#define SEARCHCHANNEL_H
#include "innertube/objects/genericthumbnail.h"
#include "innertube/objects/innertubestring.h"

namespace InnertubeObjects
{
    class SearchChannel
    {
    public:
        QString channelId;
        InnertubeString descriptionSnippet;
        bool subscribed;
        InnertubeString subscriberCountText;
        QVector<GenericThumbnail> thumbnails;
        InnertubeString title;
        InnertubeString videoCountText;
        explicit SearchChannel(const QJsonValue& channelRenderer);
    };
}

#endif // SEARCHCHANNEL_H
