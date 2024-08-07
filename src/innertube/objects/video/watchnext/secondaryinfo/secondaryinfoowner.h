#pragma once
#include "innertube/objects/channel/metadatabadge.h"
#include "innertube/objects/images/responsiveimage.h"
#include "innertube/objects/innertubestring.h"

namespace InnertubeObjects
{
    struct SecondaryInfoOwner
    {
        QList<MetadataBadge> badges;
        QJsonValue navigationEndpoint;
        InnertubeString subscriberCountText;
        QString subscriptionType;
        ResponsiveImage thumbnail;
        InnertubeString title;

        SecondaryInfoOwner() = default;
        explicit SecondaryInfoOwner(const QJsonValue& videoOwnerRenderer);
    };
}
