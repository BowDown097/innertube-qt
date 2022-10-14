#ifndef NEXT_H
#define NEXT_H
#include "../base/baseendpoint.h"

namespace InnertubeEndpoints
{
    class Next : public BaseEndpoint
    {
        friend class ::InnerTube;
        Next(const QString& videoId, InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore);
    };
}

#endif // NEXT_H
