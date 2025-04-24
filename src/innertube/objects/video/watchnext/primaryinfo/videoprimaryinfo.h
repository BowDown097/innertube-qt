#pragma once
#include "videoactions.h"
#include "viewcount.h"

namespace InnertubeObjects
{
    struct VideoPrimaryInfo
    {
        InnertubeString dateText;
        InnertubeString relativeDateText;
        InnertubeString superTitleLink;
        InnertubeString title;
        QJsonValue updatedMetadataEndpoint;
        VideoActions videoActions;
        ViewCount viewCount;

        VideoPrimaryInfo() = default;
        explicit VideoPrimaryInfo(const QJsonValue& primaryInfoRenderer)
            : dateText(primaryInfoRenderer["dateText"]),
              relativeDateText(primaryInfoRenderer["relativeDateText"]),
              superTitleLink(primaryInfoRenderer["superTitleLink"]),
              title(primaryInfoRenderer["title"]),
              videoActions(primaryInfoRenderer["videoActions"]["menuRenderer"]),
              viewCount(primaryInfoRenderer["viewCount"]["videoViewCountRenderer"]) {}
    };
}
