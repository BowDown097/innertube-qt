#ifndef HOMERESPONSE_H
#define HOMERESPONSE_H
#include "innertube/objects/video/video.h"

namespace InnertubeEndpoints
{
    struct HomeResponse
    {
        QList<InnertubeObjects::InnertubeString> shelves;
        QList<InnertubeObjects::Video> videos;
    };
}

#endif // HOMERESPONSE_H
