#ifndef NEXT_H
#define NEXT_H
#include "innertube/endpoints/base/baseendpoint.h"
#include "innertube/responses/video/nextresponse.h"

namespace InnertubeEndpoints
{
    /**
     * @brief Most of the data, such as the title, description, and comments, for a video.
     */
    class Next : public BaseEndpoint
    {
        friend class ::InnerTube;
    public:
        NextResponse response;
    protected:
        /**
         * @param tokenIn  UNIMPLEMENTED - Continuation token for comments.
         */
        Next(const QString& videoId, InnertubeContext* context, InnertubeAuthStore* authStore, const QString& tokenIn);
    };
}

#endif // NEXT_H
