#ifndef NEXT_H
#define NEXT_H
#include "innertube/endpoints/base/baseendpoint.h"
#include "innertube/responses/video/nextresponse.h"

namespace InnertubeEndpoints
{
    class Next : public BaseEndpoint
    {
        friend class ::InnerTube;
    public:
        NextResponse response;
    private:
        Next(const QString& videoId, InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore, const QString& tokenIn);
    };
}

#endif // NEXT_H
