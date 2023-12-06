#ifndef CHANNELHEADER_H
#define CHANNELHEADER_H
#include "channelheaderlink.h"
#include "innertube/objects/responsiveimage.h"
#include "subscribebutton.h"

namespace InnertubeObjects
{
    struct ChannelHeader
    {
        ResponsiveImage avatar;
        ResponsiveImage banner;
        InnertubeString channelHandleText;
        QString channelId;
        ResponsiveImage mobileBanner;
        QList<ChannelHeaderLink> primaryLinks;
        QList<ChannelHeaderLink> secondaryLinks;
        SubscribeButton subscribeButton;
        InnertubeString subscriberCountText;
        QString title;
        ResponsiveImage tvBanner;
        InnertubeString videosCountText;

        ChannelHeader() = default;
        explicit ChannelHeader(const QJsonValue& headerRenderer);
    };
}

#endif // CHANNELHEADER_H
