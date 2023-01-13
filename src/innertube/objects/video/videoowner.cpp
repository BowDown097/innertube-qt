#include "videoowner.h"
#include <QJsonArray>
#include <QJsonObject>

namespace InnertubeObjects
{
    VideoOwner::VideoOwner(const QJsonValue& textVal, const QJsonValue& thumbnailVal, bool isGridVideo)
    {
        const QJsonValue& run = textVal["runs"].toArray()[0];
        id = run["navigationEndpoint"]["browseEndpoint"]["browseId"].toString();
        name = run["text"].toString();

        const QJsonArray thumbnails = isGridVideo
                ? thumbnailVal.toObject().constBegin()->toArray()
                : thumbnailVal.toObject().constBegin()->toObject()["thumbnail"].toObject()["thumbnails"].toArray();
        icon = thumbnails[thumbnails.count() - 1]["url"].toString();
    }
}
