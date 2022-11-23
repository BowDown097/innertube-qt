#include "videoowner.h"
#include <QJsonArray>
#include <QJsonObject>

namespace InnertubeObjects
{
    VideoOwner::VideoOwner(const QJsonValue& textVal, const QJsonValue& thumbnailVal, bool isGridVideo)
    {
        QJsonValue run = textVal["runs"].toArray()[0];
        id = run["navigationEndpoint"]["browseEndpoint"]["browseId"].toString();
        name = run["text"].toString();

        QJsonArray thumbnails = isGridVideo
                ? thumbnailVal.toObject().begin()->toArray()
                : thumbnailVal.toObject().begin()->toObject()["thumbnail"].toObject()["thumbnails"].toArray();
        icon = thumbnails[thumbnails.count() - 1].toObject()["url"].toString();
    }
}
