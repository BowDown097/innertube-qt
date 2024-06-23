#pragma once
#include "innertube/objects/responsiveimage.h"
#include "metadatabadge.h"
#include "subscribebutton.h"

namespace InnertubeObjects
{
    struct Channel
    {
        QString channelId;
        InnertubeString descriptionSnippet;
        InnertubeString longBylineText;
        QJsonValue navigationEndpoint;
        QList<MetadataBadge> ownerBadges;
        InnertubeString shortBylineText;
        SubscribeButton subscribeButton;
        bool subscribed{};
        InnertubeString subscriberCountText;
        ResponsiveImage thumbnail;
        InnertubeString title;
        InnertubeString videoCountText;

        Channel() = default;
        explicit Channel(const QJsonValue& channelRenderer);
    };
}
