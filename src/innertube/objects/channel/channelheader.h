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
        QList<GenericThumbnail> avatars;
        QList<GenericThumbnail> banners;
        InnertubeString channelHandleText;
        QString channelId;
        QList<GenericThumbnail> mobileBanners;
        QList<ChannelHeaderLink> primaryLinks;
        QList<ChannelHeaderLink> secondaryLinks;
        SubscribeButton subscribeButton;
        InnertubeString subscriberCountText;
        QString title;
        QList<GenericThumbnail> tvBanners;
        InnertubeString videosCountText;

        ChannelHeader() {}
        explicit ChannelHeader(const QJsonValue& headerRenderer);
    };
}

#endif // CHANNELHEADER_H
