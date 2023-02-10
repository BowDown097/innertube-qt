#ifndef UPDATEDMETADATARESPONSE_H
#define UPDATEDMETADATARESPONSE_H
#include "innertube/objects/innertubestring.h"

namespace InnertubeEndpoints
{
    struct UpdatedMetadataResponse
    {
        QString dateText;
        InnertubeObjects::InnertubeString description;
        bool isLive;
        QString likeDefaultText;
        QString likeToggledText;
        InnertubeObjects::InnertubeString title;
        QString viewCount;
    };
}

#endif // UPDATEDMETADATARESPONSE_H
