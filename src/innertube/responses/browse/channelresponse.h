#ifndef CHANNELRESPONSE_H
#define CHANNELRESPONSE_H
#include "innertube/objects/channel/channelheader.h"
#include "innertube/objects/video/video.h"

namespace InnertubeEndpoints
{
    struct ChannelResponse
    {
        QList<InnertubeObjects::ChannelHeader> header;
        QList<InnertubeObjects::Video> videos;
    };
}

#endif // CHANNELRESPONSE_H
