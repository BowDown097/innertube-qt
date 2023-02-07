#ifndef VIDEO_H
#define VIDEO_H
#include "innertube/objects/innertubestring.h"
#include "videoowner.h"
#include "videothumbnail.h"

namespace InnertubeObjects
{
    class Video
    {
    public:
        InnertubeString descriptionSnippet;
        bool isLive;
        InnertubeString lengthText;
        InnertubeString longBylineText;
        VideoOwner owner;
        InnertubeString publishedTimeText;
        InnertubeString shelf;
        InnertubeString shortBylineText;
        InnertubeString shortViewCountText;
        bool showActionMenu;
        int startTimeSeconds;
        VideoThumbnail thumbnail;
        InnertubeString title;
        QString videoId;
        InnertubeString viewCountText;

        Video(const QJsonValue& videoRenderer, bool isGridVideo, const InnertubeString& shelf = InnertubeString());
    };
}

#endif // VIDEO_H
