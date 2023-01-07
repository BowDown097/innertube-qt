#ifndef SUBSCRIBE_H
#define SUBSCRIBE_H
#include "innertube/endpoints/base/baseendpoint.h"

namespace InnertubeEndpoints
{
    class Subscribe : public BaseEndpoint
    {
        friend class ::InnerTube;
    public:
        Subscribe(const QStringList& channelIds, const QString& params, bool subscribing, InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore);
    };
}

#endif // SUBSCRIBE_H
