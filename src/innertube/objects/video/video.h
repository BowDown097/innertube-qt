#ifndef VIDEO_H
#define VIDEO_H
#include "innertube/objects/innertubestring.h"
#include "videoowner.h"
#include "videothumbnail.h"
#include <QTime>

namespace InnertubeObjects
{
    struct Video
    {
        InnertubeString descriptionSnippet;
        bool isLive;
        InnertubeString lengthText;
        InnertubeString longBylineText;
        QJsonValue navigationEndpoint;
        VideoOwner owner;
        InnertubeString publishedTimeText;
        InnertubeString shelf;
        InnertubeString shortBylineText;
        InnertubeString shortViewCountText;
        bool showActionMenu;
        VideoThumbnail thumbnail;
        InnertubeString title;
        QString videoId;
        InnertubeString viewCountText;

        Video(const QJsonValue& videoRenderer, bool isGridVideo, const InnertubeString& shelf = InnertubeString());
        bool isReel() const;
        QTime length() const;
    };
}

#endif // VIDEO_H
