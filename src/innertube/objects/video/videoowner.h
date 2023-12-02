#ifndef VIDEOOWNER_H
#define VIDEOOWNER_H
#include "innertube/objects/channel/metadatabadge.h"

namespace InnertubeObjects
{
    struct VideoOwner
    {
        QList<MetadataBadge> badges;
        QString icon;
        QString id;
        QString name;

        VideoOwner() = default;
        VideoOwner(const QJsonValue& textVal, const QJsonValue& thumbnailVal, const QJsonValue& badgesVal, bool isGridVideo);
    };
}

#endif // VIDEOOWNER_H
