#ifndef GENERICTHUMBNAIL_H
#define GENERICTHUMBNAIL_H
#include <QJsonValue>

namespace InnertubeObjects
{
    class GenericThumbnail
    {
    public:
        int height;
        QString url;
        int width;

        GenericThumbnail(const QJsonValue& value)
            : height(value["height"].toInt()),
              url(value["url"].toString()),
              width(value["width"].toInt()) {}

        GenericThumbnail(int height, const QString& url, int width)
            : height(height),
              url(url),
              width(width) {}
    };
}

#endif // GENERICTHUMBNAIL_H
