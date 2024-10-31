#pragma once
#include "baselikeendpoint.h"

namespace InnertubeEndpoints
{
    /**
     * @brief Dislike a video.
     */
    class Dislike : public BaseLikeEndpoint<"like/dislike">
    {
        friend class ::InnerTube;
    protected:
        Dislike(const InnertubeContext* context, const InnertubeAuthStore* authStore,
                const QString& videoId, const QString& params)
            : BaseLikeEndpoint<"like/dislike">(context, authStore, videoId, params) {}
    };
}
