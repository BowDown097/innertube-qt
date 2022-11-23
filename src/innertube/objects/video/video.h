#ifndef VIDEO_H
#define VIDEO_H
#include "innertube/objects/innertubestring.h"
#include "videoowner.h"
#include "videothumbnail.h"
#include <QJsonValue>

namespace InnertubeObjects
{
    class Video
    {
    public:
        bool isLive;
        InnertubeString lengthText;
        VideoOwner owner;
        InnertubeString publishedTimeText;
        InnertubeString shelf;
        InnertubeString shortViewCountText;
        int startTimeSeconds;
        VideoThumbnail thumbnail;
        InnertubeString title;
        QString videoId;
        InnertubeString viewCountText;

        Video(const QJsonValue& videoRenderer, bool isGridVideo, const InnertubeString& shelf = InnertubeString());
    };
}

#endif // VIDEO_H
