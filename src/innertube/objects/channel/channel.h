#pragma once
#include "innertube/objects/images/responsiveimage.h"
#include "metadatabadge.h"
#include "subscribebutton.h"
#include "subscriptionbutton.h"

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
        SubscriptionButton subscriptionButton; // yes, subscribeButton and subscriptionButton are 2 different things
        InnertubeString subscriberCountText;
        ResponsiveImage thumbnail;
        InnertubeString title;
        InnertubeString videoCountText;

        Channel() = default;
        explicit Channel(const QJsonValue& channelRenderer);
    };
}
