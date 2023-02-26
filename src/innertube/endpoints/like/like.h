#ifndef LIKE_H
#define LIKE_H
#include "innertube/endpoints/base/baseendpoint.h"

namespace InnertubeEndpoints
{
    class Like : public BaseEndpoint
    {
        friend class ::InnerTube;
    public:
        Like(const QString& videoId, const QString& params, bool liking, bool removeLike, InnertubeContext* context, CurlEasy* easy,
             InnertubeAuthStore* authStore);
    };
}

#endif // LIKE_H
