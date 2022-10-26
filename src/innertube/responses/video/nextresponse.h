#ifndef NEXTRESPONSE_H
#define NEXTRESPONSE_H
#include "innertube/objects/video/video.h"
#include "innertube/objects/video/videoprimaryinfo.h"
#include "innertube/objects/video/videosecondaryinfo.h"

namespace InnertubeEndpoints
{
    struct NextResponse
    {
        InnertubeObjects::VideoPrimaryInfo primaryInfo;
        QList<InnertubeObjects::Video> relatedVideos;
        InnertubeObjects::VideoSecondaryInfo secondaryInfo;
    };
}

#endif // NEXTRESPONSE_H
