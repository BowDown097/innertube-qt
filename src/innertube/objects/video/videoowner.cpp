#include "videoowner.h"
#include <QJsonArray>
#include <QJsonObject>

namespace InnertubeObjects
{
    VideoOwner::VideoOwner(const QJsonValue& textVal, const QJsonValue& thumbnailVal, const QJsonArray& badgesJson)
        : id(textVal["runs"][0]["navigationEndpoint"]["browseEndpoint"]["browseId"].toString()),
          name(textVal["runs"][0]["text"].toString())
    {
        if (thumbnailVal.isObject())
        {
            const QJsonObject thumbnailObj = thumbnailVal.toObject();
            auto thumbnailBegin = thumbnailObj.begin();
            if (thumbnailBegin != thumbnailObj.end())
            {
                const QJsonValue& value = thumbnailBegin.value();
                icon = ResponsiveImage(thumbnailBegin->isArray() ? value : value["thumbnail"]["thumbnails"]);
            }
        }

        for (const QJsonValue& v : badgesJson)
            badges.append(MetadataBadge(v["metadataBadgeRenderer"]));
    }
}
