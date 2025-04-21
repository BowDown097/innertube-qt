#pragma once
#include "baselikeendpoint.h"

namespace InnertubeEndpoints
{
    /**
     * @brief Remove your like from a video.
     */
    struct RemoveLike : BaseLikeEndpoint<"like/removelike"> {};
}
