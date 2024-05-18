#pragma once
#include "innertube/objects/video/video.h"

namespace InnertubeEndpoints
{
    struct HistoryResponse
    {
        QList<InnertubeObjects::Video> videos;
    };
}
