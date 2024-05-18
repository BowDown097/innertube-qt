#pragma once
#include "innertube/objects/responsiveimage.h"
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
        ResponsiveImage thumbnail;
        InnertubeString title;
        InnertubeString videoCountText;

        explicit Channel(const QJsonValue& channelRenderer)
            : channelId(channelRenderer["channelId"].toString()),
              descriptionSnippet(InnertubeString(channelRenderer["descriptionSnippet"])),
              subscribeButton(channelRenderer["subscribeButton"]["subscribeButtonRenderer"]),
              subscribed(channelRenderer["subscriptionButton"]["subscribed"].toBool()),
              subscriberCountText(InnertubeString(channelRenderer["subscriberCountText"])),
              thumbnail(channelRenderer["thumbnail"]["thumbnails"]),
              title(InnertubeString(channelRenderer["title"])),
              videoCountText(InnertubeString(channelRenderer["videoCountText"])) {}
    };
}
