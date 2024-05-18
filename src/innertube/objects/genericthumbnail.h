#pragma once
#include <QJsonValue>

namespace InnertubeObjects
{
    struct GenericThumbnail
    {
        int height;
        QString url;
        int width;

        explicit GenericThumbnail(const QJsonValue& value)
            : height(value["height"].toInt()),
              url(value["url"].toString()),
              width(value["width"].toInt()) {}

        GenericThumbnail(int height, const QString& url, int width)
            : height(height),
              url(url),
              width(width) {}
    };
}
