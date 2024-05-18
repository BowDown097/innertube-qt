#pragma once
#include "innertube/objects/channel/channel.h"
#include "innertube/objects/video/video.h"

namespace InnertubeEndpoints
{
    struct SearchResponse
    {
        QList<InnertubeObjects::Channel> channels;
        long estimatedResults;
        QList<InnertubeObjects::Video> videos;
    };
}
