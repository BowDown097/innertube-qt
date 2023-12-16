#ifndef NEXT_H
#define NEXT_H
#include "innertube/endpoints/base/baseendpoint.h"
#include "innertube/responses/video/nextresponse.h"

namespace InnertubeEndpoints
{
    /**
     * @brief Most of the data, such as the title, description, and comments, for a video.
     */
    class Next : public BaseEndpoint<"next">
    {
        friend class ::InnerTube;
    public:
        NextResponse response;
    protected:
        /**
         * @param tokenIn  Continuation token for comments.
         */
        Next(InnertubeContext* context, InnertubeAuthStore* authStore, const QString& videoId, const QString& tokenIn = "");
    };
}

#endif // NEXT_H
