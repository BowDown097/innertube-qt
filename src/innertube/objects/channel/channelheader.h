#ifndef CHANNELHEADER_H
#define CHANNELHEADER_H
#include "channelheaderlink.h"
#include "subscribebutton.h"
#include "innertube/objects/genericthumbnail.h"
#include "innertube/objects/innertubestring.h"

namespace InnertubeObjects
{
    class ChannelHeader
    {
    public:
        QList<GenericThumbnail> avatar;
        QList<GenericThumbnail> banner;
        InnertubeString channelHandleText;
        QString channelId;
        QList<GenericThumbnail> mobileBanner;
        QList<ChannelHeaderLink> primaryLinks;
        QList<ChannelHeaderLink> secondaryLinks;
        SubscribeButton subscribeButton;
        InnertubeString subscriberCountText;
        QString title;
        QList<GenericThumbnail> tvBanner;
        InnertubeString videosCountText;

        ChannelHeader();
        explicit ChannelHeader(const QJsonValue& headerRenderer);
    };
}

#endif // CHANNELHEADER_H
