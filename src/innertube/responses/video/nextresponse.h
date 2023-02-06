#ifndef NEXTRESPONSE_H
#define NEXTRESPONSE_H
#include "innertube/objects/video/primaryinfo/videoprimaryinfo.h"
#include "innertube/objects/video/secondaryinfo/videosecondaryinfo.h"

namespace InnertubeEndpoints
{
    struct NextResponse
    {
        InnertubeObjects::VideoPrimaryInfo primaryInfo;
        InnertubeObjects::VideoSecondaryInfo secondaryInfo;
    };
}

#endif // NEXTRESPONSE_H
