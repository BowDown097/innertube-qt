#pragma once
#include "innertube/objects/video/video.h"

namespace InnertubeEndpoints
{
    struct TrendingResponse
    {
        QList<InnertubeObjects::InnertubeString> shelves;
        QList<InnertubeObjects::Video> videos;
    };
}
