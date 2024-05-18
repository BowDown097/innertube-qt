#pragma once
#include "innertube/objects/entitymutation.h"
#include "innertube/objects/channel/channelc4header.h"
#include "innertube/objects/channel/channelpageheader.h"
#include "innertube/objects/channel/channelmetadata.h"
#include "innertube/objects/channel/microformatdata.h"

namespace InnertubeEndpoints
{
    struct ChannelResponse
    {
        QJsonValue contents;
        std::variant<InnertubeObjects::ChannelC4Header, InnertubeObjects::ChannelPageHeader> header;
        InnertubeObjects::ChannelMetadata metadata;
        InnertubeObjects::MicroformatData microformat;
        QList<InnertubeObjects::EntityMutation> mutations;
    };
}
