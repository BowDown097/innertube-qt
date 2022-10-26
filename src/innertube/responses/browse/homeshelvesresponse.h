#ifndef HOMESHELVESRESPONSE_H
#define HOMESHELVESRESPONSE_H
#include "innertube/objects/video/video.h"

namespace InnertubeEndpoints
{
    struct HomeShelvesResponse
    {
        QList<InnertubeObjects::InnertubeString> shelves;
        QList<InnertubeObjects::Video> videos;
    };
}

#endif // HOMESHELVESRESPONSE_H
