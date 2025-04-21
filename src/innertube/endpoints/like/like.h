#pragma once
#include "baselikeendpoint.h"

namespace InnertubeEndpoints
{
    /**
     * @brief Like a video.
     */
    struct Like : BaseLikeEndpoint<"like/like"> {};
}
