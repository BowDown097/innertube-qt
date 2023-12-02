#ifndef SECONDARYINFOOWNER_H
#define SECONDARYINFOOWNER_H
#include "innertube/objects/channel/metadatabadge.h"
#include "innertube/objects/genericthumbnail.h"
#include "innertube/objects/innertubestring.h"

namespace InnertubeObjects
{
    struct SecondaryInfoOwner
    {
        QList<MetadataBadge> badges;
        QJsonValue navigationEndpoint;
        InnertubeString subscriberCountText;
        QString subscriptionType;
        QList<GenericThumbnail> thumbnails;
        InnertubeString title;

        SecondaryInfoOwner() = default;
        explicit SecondaryInfoOwner(const QJsonValue& videoOwnerRenderer);
    };
}

#endif // SECONDARYINFOOWNER_H
