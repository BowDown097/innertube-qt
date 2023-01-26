#ifndef CHANNELRESPONSE_H
#define CHANNELRESPONSE_H
#include "innertube/objects/channel/channelheader.h"
#include "innertube/objects/channel/channelmetadata.h"

namespace InnertubeEndpoints
{
    struct ChannelResponse
    {
        InnertubeObjects::ChannelHeader header;
        InnertubeObjects::ChannelMetadata metadata;
    };
}

#endif // CHANNELRESPONSE_H
