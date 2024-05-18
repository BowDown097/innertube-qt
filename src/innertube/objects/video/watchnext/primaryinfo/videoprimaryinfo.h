#pragma once
#include "videoactions.h"
#include "viewcount.h"

namespace InnertubeObjects
{
    struct VideoPrimaryInfo
    {
        InnertubeString dateText;
        InnertubeString relativeDateText;
        std::optional<InnertubeString> superTitleLink;
        InnertubeString title;
        VideoActions videoActions;
        ViewCount viewCount;

        VideoPrimaryInfo() = default;
        explicit VideoPrimaryInfo(const QJsonValue& primaryInfoRenderer)
            : dateText(primaryInfoRenderer["dateText"]),
              relativeDateText(primaryInfoRenderer["relativeDateText"]),
              superTitleLink(primaryInfoRenderer["superTitleLink"].isObject()
                             ? std::make_optional<InnertubeString>(primaryInfoRenderer["superTitleLink"])
                             : std::nullopt),
              title(primaryInfoRenderer["title"]),
              videoActions(primaryInfoRenderer["videoActions"]["menuRenderer"]),
              viewCount(primaryInfoRenderer["viewCount"]["videoViewCountRenderer"]) {}
    };
}
