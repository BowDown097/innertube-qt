#pragma once
#include "innertube/endpoints/base/baseendpoint.h"
#include "innertube/responses/video/playerresponse.h"

namespace InnertubeEndpoints
{
    /**
     * @brief Data used for the player, such as streams, for a video.
     */
    class Player : public BaseEndpoint<"player">
    {
        friend class ::InnerTube;
    public:
        PlayerResponse response;
    protected:
        Player(InnertubeContext* context, InnertubeAuthStore* authStore, const QString& videoId);
    };
}
