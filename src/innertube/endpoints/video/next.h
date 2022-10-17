#ifndef NEXT_H
#define NEXT_H
#include "../base/baseendpoint.h"
#include "innertube/objects/video/video.h"
#include "innertube/objects/video/videoprimaryinfo.h"
#include "innertube/objects/video/videosecondaryinfo.h"

namespace InnertubeEndpoints
{
    class Next : public BaseEndpoint
    {
        friend class ::InnerTube;
    public:
        InnertubeObjects::VideoPrimaryInfo primaryInfo;
        QList<InnertubeObjects::Video> relatedVideos;
        InnertubeObjects::VideoSecondaryInfo secondaryInfo;
    private:
        Next(const QString& videoId, InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore, const QString& tokenIn);
    };
}

#endif // NEXT_H
