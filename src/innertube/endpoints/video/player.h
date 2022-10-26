#ifndef PLAYER_H
#define PLAYER_H
#include "innertube/endpoints/base/baseendpoint.h"
#include "innertube/responses/video/playerresponse.h"

namespace InnertubeEndpoints
{
    class Player : public BaseEndpoint
    {
        friend class ::InnerTube;
    public:
        PlayerResponse response;
    private:
        Player(const QString& videoId, InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore);
    };
}


#endif // PLAYER_H
