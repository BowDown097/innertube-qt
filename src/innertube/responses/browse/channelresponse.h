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
        QJsonValue contents; // this will be the only member to have a value if the origin of the request is a continuation
        std::variant<InnertubeObjects::ChannelC4Header, InnertubeObjects::ChannelPageHeader, std::monostate> header;
        InnertubeObjects::ChannelMetadata metadata;
        InnertubeObjects::MicroformatData microformat;
        QList<InnertubeObjects::EntityMutation> mutations;
    };
}
