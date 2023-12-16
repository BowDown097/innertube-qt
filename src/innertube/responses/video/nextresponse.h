#ifndef NEXTRESPONSE_H
#define NEXTRESPONSE_H
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

#endif // NEXTRESPONSE_H
