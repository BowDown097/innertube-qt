#ifndef CHANNELRESPONSE_H
#define CHANNELRESPONSE_H
#include "innertube/objects/video/video.h"

namespace InnertubeEndpoints
{
    struct ChannelResponse
    {
        QList<InnertubeObjects::Video> videos;
    };
}

#endif // CHANNELRESPONSE_H
