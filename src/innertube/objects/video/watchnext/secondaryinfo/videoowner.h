#pragma once
#include "innertube/objects/channel/metadatabadge.h"
#include "innertube/objects/channel/subscriptionbutton.h"
#include "innertube/objects/images/responsiveimage.h"
#include "innertube/objects/items/button.h"
#include "innertube/objects/innertubestring.h"

namespace InnertubeObjects
{
    struct VideoOwner
    {
        QList<MetadataBadge> badges;
        std::optional<Button> membershipButton;
        QJsonValue navigationEndpoint;
        InnertubeString subscriberCountText;
        SubscriptionButton subscriptionButton;
        ResponsiveImage thumbnail;
        InnertubeString title;

        VideoOwner() = default;
        explicit VideoOwner(const QJsonValue& videoOwnerRenderer);
    };
}
