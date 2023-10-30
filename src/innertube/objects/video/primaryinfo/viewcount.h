#ifndef VIEWCOUNT_H
#define VIEWCOUNT_H
#include "innertube/objects/innertubestring.h"

namespace InnertubeObjects
{
    class ViewCount
    {
    public:
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

#endif // VIEWCOUNT_H
