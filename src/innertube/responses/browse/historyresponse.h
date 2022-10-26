#ifndef HISTORYRESPONSE_H
#define HISTORYRESPONSE_H
#include "innertube/objects/video/video.h"

namespace InnertubeEndpoints
{
    struct HistoryResponse
    {
        QList<InnertubeObjects::Video> videos;
    };
}

#endif // HISTORYRESPONSE_H
