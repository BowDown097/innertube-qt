#pragma once
#include "innertube/objects/images/responsiveimage.h"
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
        std::variant<SubscribeButton, Button> subscribeButton; // will be plain Button if logged out
        bool subscribed{};
        InnertubeString subscriberCountText;
        ResponsiveImage thumbnail;
        InnertubeString title;
        InnertubeString videoCountText;

        Channel() = default;
        explicit Channel(const QJsonValue& channelRenderer);
    };
}
