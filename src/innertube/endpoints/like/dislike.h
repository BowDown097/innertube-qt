#ifndef DISLIKE_H
#define DISLIKE_H
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
        Dislike(InnertubeContext* context, InnertubeAuthStore* authStore, const QString& videoId, const QString& params)
            : BaseLikeEndpoint<"like/dislike">(context, authStore, videoId, params) {}
    };
}

#endif // DISLIKE_H
