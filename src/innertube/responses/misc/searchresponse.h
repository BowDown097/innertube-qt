#ifndef SEARCHRESPONSE_H
#define SEARCHRESPONSE_H
#include "innertube/objects/channel/searchchannel.h"
#include "innertube/objects/video/video.h"

namespace InnertubeEndpoints
{
    struct SearchResponse
    {
        QList<InnertubeObjects::SearchChannel> channels;
        long estimatedResults;
        QList<InnertubeObjects::Video> videos;
    };
}

#endif // SEARCHRESPONSE_H
