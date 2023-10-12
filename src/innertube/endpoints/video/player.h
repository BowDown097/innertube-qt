#ifndef PLAYER_H
#define PLAYER_H
#include "innertube/endpoints/base/baseendpoint.h"
#include "innertube/responses/video/playerresponse.h"

namespace InnertubeEndpoints
{
    /**
     * @brief Data used for the player, such as streams, for a video.
     */
    class Player : public BaseEndpoint
    {
        friend class ::InnerTube;
    public:
        PlayerResponse response;
    protected:
        Player(const QString& videoId, InnertubeContext* context, InnertubeAuthStore* authStore);
    };
}


#endif // PLAYER_H
