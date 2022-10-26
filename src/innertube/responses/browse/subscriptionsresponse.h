#ifndef SUBSCRIPTIONSRESPONSE_H
#define SUBSCRIPTIONSRESPONSE_H
#include "innertube/objects/video/video.h"

namespace InnertubeEndpoints
{
    struct SubscriptionsResponse
    {
        QList<InnertubeObjects::Video> videos;
    };
}

#endif // SUBSCRIPTIONSRESPONSE_H
