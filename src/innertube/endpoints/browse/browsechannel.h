#ifndef BROWSECHANNEL_H
#define BROWSECHANNEL_H
#include "../base/basebrowseendpoint.h"

namespace InnertubeEndpoints
{
    class BrowseChannel : public BaseBrowseEndpoint
    {
        friend class ::InnerTube;
        BrowseChannel(const QString& channelId, InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore)
            : BaseBrowseEndpoint(channelId, context, easy, authStore) {}
    };
}

#endif // BROWSECHANNEL_H
