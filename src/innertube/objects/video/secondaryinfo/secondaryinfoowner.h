#ifndef SECONDARYINFOOWNER_H
#define SECONDARYINFOOWNER_H
#include "innertube/objects/channel/metadatabadge.h"
#include "innertube/objects/genericthumbnail.h"
#include "innertube/objects/innertubestring.h"

namespace InnertubeObjects
{
    class SecondaryInfoOwner
    {
    public:
        QList<MetadataBadge> badges;
        InnertubeString subscriberCountText;
        QString subscriptionType;
        QList<GenericThumbnail> thumbnails;
        InnertubeString title;

        SecondaryInfoOwner() {}
        explicit SecondaryInfoOwner(const QJsonValue& videoOwnerRenderer);
    };
}

#endif // SECONDARYINFOOWNER_H
