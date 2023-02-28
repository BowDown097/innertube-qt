#include "like.h"

namespace InnertubeEndpoints
{
    Like::Like(const QString& videoId, const QString& params, bool liking, bool removeLike, InnertubeContext* context, InnertubeAuthStore* authStore)
    {
        const QJsonObject body {
            { "context", context->toJson() },
            { "params", params },
            { "target", QJsonObject { { "videoId", videoId } } }
        };

        if (removeLike)
            get("like/removelike", context, authStore, body);
        else
            get(liking ? "like/like" : "like/dislike", context, authStore, body);
    }
}
