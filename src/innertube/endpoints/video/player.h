#pragma once
#include "innertube/endpoints/base/baseendpoint.h"
#include "innertube/responses/video/playerresponse.h"

namespace InnertubeEndpoints
{
    /**
     * @brief Data used for the player, such as streams, for a video.
     */
    struct Player : BaseEndpoint<"player">
    {
        PlayerResponse response;

        explicit Player(const QJsonValue& data);
        static QJsonObject createBody(const InnertubeContext* context, const QString& videoId, const QString& poToken = {});
    };
}
