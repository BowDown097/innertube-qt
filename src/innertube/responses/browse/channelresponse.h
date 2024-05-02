#ifndef CHANNELRESPONSE_H
#define CHANNELRESPONSE_H
#include "innertube/objects/entitymutation.h"
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
        QList<InnertubeObjects::EntityMutation> mutations;
    };
}

#endif // CHANNELRESPONSE_H
