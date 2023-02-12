#include "videoowner.h"
#include <QJsonArray>
#include <QJsonObject>

namespace InnertubeObjects
{
    VideoOwner::VideoOwner(const QJsonValue& textVal, const QJsonValue& thumbnailVal, const QJsonValue& badgesVal, bool isGridVideo)
        : id(textVal["runs"][0]["navigationEndpoint"]["browseEndpoint"]["browseId"].toString()),
          name(textVal["runs"][0]["text"].toString())
    {
        if (!thumbnailVal.isUndefined())
        {
            const QJsonArray thumbnails = isGridVideo
                    ? thumbnailVal.toObject().constBegin()->toArray()
                    : thumbnailVal.toObject().constBegin()->toObject()["thumbnail"].toObject()["thumbnails"].toArray();
            icon = thumbnails[thumbnails.count() - 1]["url"].toString();
        }

        const QJsonArray badgesJson = badgesVal.toArray();
        for (const QJsonValue& v : badgesJson)
            badges.append(MetadataBadge(v["metadataBadgeRenderer"]));
    }
}
