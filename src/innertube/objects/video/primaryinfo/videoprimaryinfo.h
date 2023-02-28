#ifndef VIDEOPRIMARYINFO_H
#define VIDEOPRIMARYINFO_H
#include "videoactions.h"

namespace InnertubeObjects
{
    class VideoPrimaryInfo
    {
    public:
        InnertubeString dateText;
        InnertubeString relativeDateText;
        InnertubeString shortViewCount;
        InnertubeString title;
        VideoActions videoActions;
        InnertubeString viewCount;

        VideoPrimaryInfo() = default;
        explicit VideoPrimaryInfo(const QJsonValue& primaryInfoRenderer)
            : dateText(primaryInfoRenderer["dateText"]),
              relativeDateText(primaryInfoRenderer["relativeDateText"]),
              shortViewCount(primaryInfoRenderer["viewCount"]["videoViewCountRenderer"]["shortViewCount"]),
              title(primaryInfoRenderer["title"]),
              videoActions(primaryInfoRenderer["videoActions"]["menuRenderer"]),
              viewCount(primaryInfoRenderer["viewCount"]["videoViewCountRenderer"]["viewCount"]) {}
    };
}

#endif // VIDEOPRIMARYINFO_H
