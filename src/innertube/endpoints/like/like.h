#pragma once
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
        Like(const InnertubeContext* context, const InnertubeAuthStore* authStore,
             const QString& videoId, const QString& params)
            : BaseLikeEndpoint<"like/like">(context, authStore, videoId, params) {}
    };
}
