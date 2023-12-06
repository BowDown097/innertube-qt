#ifndef SECONDARYINFOOWNER_H
#define SECONDARYINFOOWNER_H
#include "innertube/objects/channel/metadatabadge.h"
#include "innertube/objects/innertubestring.h"
#include "innertube/objects/responsiveimage.h"

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

#endif // SECONDARYINFOOWNER_H
