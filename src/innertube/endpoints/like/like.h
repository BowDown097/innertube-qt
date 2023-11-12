#ifndef LIKE_H
#define LIKE_H
#include "baselikeendpoint.h"

namespace InnertubeEndpoints
{
    /**
     * @brief Like a video.
     */
    class Like : public BaseLikeEndpoint<"like/like">
    {
        friend class ::InnerTube;
    protected:
        Like(InnertubeContext* context, InnertubeAuthStore* authStore, const QString& videoId, const QString& params)
            : BaseLikeEndpoint<"like/like">(context, authStore, videoId, params) {}
    };
}

#endif // LIKE_H
