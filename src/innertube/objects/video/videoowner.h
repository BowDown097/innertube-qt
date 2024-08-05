#pragma once
#include "innertube/objects/channel/metadatabadge.h"
#include "innertube/objects/images/responsiveimage.h"

class QJsonArray;

namespace InnertubeObjects
{
    struct VideoOwner
    {
        QList<MetadataBadge> badges;
        ResponsiveImage icon;
        QString id;
        QString name;

        VideoOwner() = default;
        VideoOwner(const QJsonValue& textVal, const QJsonValue& thumbnailVal, const QJsonArray& badgesJson);
    };
}
