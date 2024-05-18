#pragma once
#include "innertube/objects/video/watchnext/twocolumnwatchnextresults.h"
#include "nextcontinuationdata.h"

namespace InnertubeEndpoints
{
    struct NextResponse
    {
        std::optional<NextContinuationData> continuationData;
        InnertubeObjects::TwoColumnWatchNextResults results;
        QString videoId;
    };
}
