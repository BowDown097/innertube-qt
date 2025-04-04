#include "next.h"
#include "innertube/innertubeexception.h"
#include "innertube/itc-objects/innertubeplaybackcontext.h"

namespace InnertubeEndpoints
{
    Next::Next(const InnertubeContext* context, const InnertubeAuthStore* authStore,
               const QString& videoId, const QString& tokenIn)
        : Next(get(context, authStore, createBody(context, videoId, tokenIn))) {}

    Next::Next(const QJsonValue& data)
    {
        if (const QJsonValue contents = data["contents"]; contents.isObject())
        {
            const QJsonValue watchNextResults = contents["twoColumnWatchNextResults"];
            if (!watchNextResults.isObject())
                throw InnertubeException("[Next] twoColumnWatchNextResults is not an object");

            response.results = InnertubeObjects::TwoColumnWatchNextResults(watchNextResults);
            response.videoId = data["currentVideoEndpoint"]["watchEndpoint"]["videoId"].toString();
        }
        else if (const QJsonValue onResponseReceivedEndpoints = data["onResponseReceivedEndpoints"];
                 onResponseReceivedEndpoints.isArray())
        {
            response.continuationData.emplace(onResponseReceivedEndpoints);
        }
        else
        {
            throw InnertubeException("[BrowseHome] Failed to find any content");
        }
    }

    QJsonObject Next::createBody(const InnertubeContext* context, const QString& videoId, const QString& tokenIn)
    {
        if (!tokenIn.isEmpty())
        {
            return {
                { "context", context->toJson() },
                { "continuation", tokenIn }
            };
        }

        return {
            { "autonavState", "STATE_ON" },
            { "captionsRequested", false },
            { "contentCheckOk", false },
            { "context", context->toJson() },
            { "playbackContext", InnertubePlaybackContext().toJson() },
            { "racyCheckOk", false },
            { "videoId", videoId }
        };
    }
}
