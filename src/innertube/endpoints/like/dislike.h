#pragma once
#include "baselikeendpoint.h"

namespace InnertubeEndpoints
{
    /**
     * @brief Dislike a video.
     */
    struct Dislike : BaseLikeEndpoint<"like/dislike"> {};
}
