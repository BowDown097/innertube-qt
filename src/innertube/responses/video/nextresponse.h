#pragma once
#include "innertube/objects/video/watchnext/twocolumnwatchnextresults.h"
#include "nextcontinuationdata.h"

namespace InnertubeEndpoints
{
    struct NextResponse
    {
        InnertubeObjects::TwoColumnWatchNextResults contents;
        std::optional<NextContinuationData> continuationData;
        QString videoId;
    };
}
