#pragma once
#include "innertube/objects/video/video.h"

namespace InnertubeEndpoints
{
    struct HomeResponse
    {
        QList<InnertubeObjects::InnertubeString> shelves;
        QList<InnertubeObjects::Video> videos;
    };
}
