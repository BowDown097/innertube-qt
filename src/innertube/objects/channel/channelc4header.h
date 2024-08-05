#pragma once
#include "channelheaderlink.h"
#include "innertube/objects/images/responsiveimage.h"
#include "subscribebutton.h"

namespace InnertubeObjects
{
    struct ChannelC4Header
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

        ChannelC4Header() = default;
        explicit ChannelC4Header(const QJsonValue& headerRenderer);
    };
}
