#ifndef GENERICTHUMBNAIL_H
#define GENERICTHUMBNAIL_H
#include <QString>

namespace InnertubeObjects
{
    class GenericThumbnail
    {
    public:
        int height;
        QString url;
        int width;
        GenericThumbnail(int height, const QString& url, int width) : height(height), url(url), width(width) {}
    };
}

#endif // GENERICTHUMBNAIL_H
