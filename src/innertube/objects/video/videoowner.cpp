#include "videoowner.h"
#include <QJsonArray>
#include <QJsonObject>

namespace InnertubeObjects
{
    VideoOwner::VideoOwner(const QJsonValue& textVal, const QJsonValue& thumbnailVal, bool isGridVideo)
    {
        const QJsonObject& text = textVal.toObject();
        const QJsonObject& thumbnail = thumbnailVal.toObject();

        QJsonObject run = text["runs"].toArray()[0].toObject();
        id = run["navigationEndpoint"].toObject()["browseEndpoint"].toObject()["browseId"].toString();
        name = run["text"].toString();

        QJsonArray thumbnails = isGridVideo
                ? thumbnail.begin().value().toArray()
                : thumbnail.begin().value().toObject()["thumbnail"].toObject()["thumbnails"].toArray();
        icon = thumbnails[thumbnails.count() - 1].toObject()["url"].toString();
    }
}
