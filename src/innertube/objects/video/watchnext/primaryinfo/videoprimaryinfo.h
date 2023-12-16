#ifndef VIDEOPRIMARYINFO_H
#define VIDEOPRIMARYINFO_H
#include "videoactions.h"
#include "viewcount.h"

namespace InnertubeObjects
{
    struct VideoPrimaryInfo
    {
        InnertubeString dateText;
        InnertubeString relativeDateText;
        InnertubeString title;
        VideoActions videoActions;
        ViewCount viewCount;

        VideoPrimaryInfo() = default;
        explicit VideoPrimaryInfo(const QJsonValue& primaryInfoRenderer)
            : dateText(primaryInfoRenderer["dateText"]),
              relativeDateText(primaryInfoRenderer["relativeDateText"]),
              title(primaryInfoRenderer["title"]),
              videoActions(primaryInfoRenderer["videoActions"]["menuRenderer"]),
              viewCount(primaryInfoRenderer["viewCount"]["videoViewCountRenderer"]) {}
    };
}

#endif // VIDEOPRIMARYINFO_H
