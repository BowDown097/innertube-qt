#pragma once
#include "innertube/objects/innertubestring.h"

namespace InnertubeObjects
{
    struct ViewCount
    {
        InnertubeString extraShortViewCount;
        bool isLive;
        QString originalViewCount;
        InnertubeString unlabeledViewCountValue;
        InnertubeString viewCount;

        ViewCount() = default;
        explicit ViewCount(const QJsonValue& videoViewCountRenderer)
            : extraShortViewCount(videoViewCountRenderer["extraShortViewCount"]),
              isLive(videoViewCountRenderer["isLive"].toBool()),
              originalViewCount(videoViewCountRenderer["originalViewCount"].toString()),
              unlabeledViewCountValue(videoViewCountRenderer["unlabeledViewCountValue"].toString()),
              viewCount(videoViewCountRenderer["viewCount"]) {}
    };
}
