#ifndef VIDEOOWNER_H
#define VIDEOOWNER_H
#include <QJsonObject>
#include <QString>

namespace InnertubeObjects
{
    class VideoOwner
    {
    public:
        QString icon{}, id{}, name{};
        VideoOwner() {}
        VideoOwner(const QJsonValue& textVal, const QJsonValue& thumbnailVal)
        {
            const QJsonObject& text = textVal.toObject();
            const QJsonObject& thumbnail = thumbnailVal.toObject();

            QJsonObject run = text["runs"].toArray()[0].toObject();
            id = run["navigationEndpoint"].toObject()["browseEndpoint"].toObject()["browseId"].toString();
            name = run["text"].toString();

            QJsonArray thumbnails = thumbnail.begin().value().toObject()["thumbnail"].toObject()["thumbnails"].toArray();
            icon = thumbnails[thumbnails.count() - 1].toObject()["url"].toString();
        }
    };
}

#endif // VIDEOOWNER_H
