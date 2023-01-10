#ifndef UNSEENCOUNT_H
#define UNSEENCOUNT_H
#include "innertube/endpoints/base/baseendpoint.h"

namespace InnertubeEndpoints
{
    class UnseenCount : public BaseEndpoint
    {
        friend class ::InnerTube;
    public:
        int unseenCount;
    private:
        UnseenCount(InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore);
    };
}

#endif // UNSEENCOUNT_H
