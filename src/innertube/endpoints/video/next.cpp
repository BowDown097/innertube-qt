#include "next.h"
#include "innertube/innertubeexception.h"
#include "innertube/itc-objects/innertubeplaybackcontext.h"

namespace InnertubeEndpoints
{
    Next::Next(const InnertubeContext* context, const InnertubeAuthStore* authStore,
               const QString& videoId, const QString& tokenIn)
    {
        QJsonObject body;
        if (tokenIn.isEmpty())
        {
            body = {
                { "autonavState", "STATE_ON" },
                { "captionsRequested", false },
                { "contentCheckOk", false },
                EndpointMethods::contextPair(context),
                { "playbackContext", InnertubePlaybackContext().toJson() },
                { "racyCheckOk", false },
                { "videoId", videoId }
            };
        }
        else
        {
            body = {
                EndpointMethods::contextPair(context),
                { "continuation", tokenIn }
            };
        }

        const QJsonValue data = get(context, authStore, body);
        if (tokenIn.isEmpty())
        {
            const QJsonValue watchNextResults = data["contents"]["twoColumnWatchNextResults"];
            if (!watchNextResults.isObject())
                throw InnertubeException("[Next] twoColumnWatchNextResults is not an object");

            response.results = InnertubeObjects::TwoColumnWatchNextResults(watchNextResults);
            response.videoId = data["currentVideoEndpoint"]["watchEndpoint"]["videoId"].toString();
        }
        else
        {
            const QJsonValue onResponseReceivedEndpoints = data["onResponseReceivedEndpoints"];
            if (!onResponseReceivedEndpoints.isArray())
                throw InnertubeException("[Next] onResponseReceivedEndpoints is not an array");
            response.continuationData.emplace(onResponseReceivedEndpoints);
        }
    }
}
