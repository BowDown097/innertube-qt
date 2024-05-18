#pragma once
#include "innertube/objects/video/video.h"

namespace InnertubeEndpoints
{
    struct SubscriptionsResponse
    {
        QList<InnertubeObjects::Video> videos;
    };
}
