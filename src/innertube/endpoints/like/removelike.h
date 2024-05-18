#pragma once
#include "baselikeendpoint.h"

namespace InnertubeEndpoints
{
    /**
     * @brief Remove your like from a video.
     */
    class RemoveLike : public BaseLikeEndpoint<"like/removelike">
    {
        friend class ::InnerTube;
    protected:
        RemoveLike(InnertubeContext* context, InnertubeAuthStore* authStore, const QString& videoId, const QString& params)
            : BaseLikeEndpoint<"like/removelike">(context, authStore, videoId, params) {}
    };
}
