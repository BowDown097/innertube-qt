#ifndef VIDEOOWNER_H
#define VIDEOOWNER_H
#include <QJsonValue>
#include <QString>

namespace InnertubeObjects
{
    class VideoOwner
    {
    public:
        QString icon;
        QString id;
        QString name;

        VideoOwner() {}
        VideoOwner(const QJsonValue& textVal, const QJsonValue& thumbnailVal, bool isGridVideo);
    };
}

#endif // VIDEOOWNER_H
