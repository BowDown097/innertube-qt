#ifndef CHANNELRESPONSE_H
#define CHANNELRESPONSE_H
#include "innertube/objects/channel/channelheader.h"
#include "innertube/objects/channel/channelmetadata.h"
#include "innertube/objects/channel/microformatdata.h"

namespace InnertubeEndpoints
{
    struct ChannelResponse
    {
        QJsonValue contents;
        InnertubeObjects::ChannelHeader header;
        InnertubeObjects::ChannelMetadata metadata;
        InnertubeObjects::MicroformatData microformat;
    };
}

#endif // CHANNELRESPONSE_H
