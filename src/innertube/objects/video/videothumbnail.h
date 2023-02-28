#ifndef VIDEOTHUMBNAIL_H
#define VIDEOTHUMBNAIL_H
#include <QString>

namespace InnertubeObjects
{
    class VideoThumbnail
    {
    public:
        QString hqdefault;
        QString maxresdefault;
        QString mqdefault;
        QString sddefault;

        VideoThumbnail() = default;
        explicit VideoThumbnail(const QString& videoId)
            : hqdefault(QStringLiteral("https://i.ytimg.com/vi/%1/hqdefault.jpg").arg(videoId)),
              maxresdefault(QStringLiteral("https://i.ytimg.com/vi/%1/maxresdefault.jpg").arg(videoId)),
              mqdefault(QStringLiteral("https://i.ytimg.com/vi/%1/mqdefault.jpg").arg(videoId)),
              sddefault(QStringLiteral("https://i.ytimg.com/vi/%1/sddefault.jpg").arg(videoId)) {}
    };
}

#endif // VIDEOTHUMBNAIL_H
