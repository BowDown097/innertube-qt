#ifndef BROWSECHANNEL_H
#define BROWSECHANNEL_H
#include "innertube/endpoints/base/baseendpoint.h"
#include "innertube/responses/browse/channelresponse.h"

namespace InnertubeEndpoints
{
    class BrowseChannel : public BaseEndpoint
    {
        friend class ::InnerTube;
    public:
        QString continuationToken;
        ChannelResponse response;
    private:
        BrowseChannel(const QString& channelId, InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore, const QString& tokenIn = "",
                      const QString& params = "");
    };
}

#endif // BROWSECHANNEL_H
