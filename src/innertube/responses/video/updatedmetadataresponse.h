#ifndef UPDATEDMETADATARESPONSE_H
#define UPDATEDMETADATARESPONSE_H
#include "innertube/objects/video/primaryinfo/likedislike/likecountentity.h"
#include "innertube/objects/video/primaryinfo/viewcount.h"

namespace InnertubeEndpoints
{
    struct UpdatedMetadataResponse
    {
        QString dateText;
        InnertubeObjects::InnertubeString description;
        InnertubeObjects::LikeCountEntity likeCountEntity;
        InnertubeObjects::InnertubeString title;
        QString videoId;
        InnertubeObjects::ViewCount viewCount;
    };
}

#endif // UPDATEDMETADATARESPONSE_H
