#ifndef LIKE_H
#define LIKE_H
#include "innertube/endpoints/base/baseendpoint.h"

namespace InnertubeEndpoints
{
    /**
     * @brief Change the like status of a video.
     */
    class Like : public BaseEndpoint
    {
        friend class ::InnerTube;
    protected:
        /**
         * @param params  Supplied by many sources - see [QtTube code](https://github.com/search?q=repo%3ABowDown097%2FQtTube%20likeordislike&type=code) for usage.
         * @param liking  Whether the user is liking or disliking.
         * @param removeLike  If a like/dislike is being removed.
         */
        Like(const QString& videoId, const QString& params, bool liking, bool removeLike, InnertubeContext* context,
             InnertubeAuthStore* authStore);
    };
}

#endif // LIKE_H
