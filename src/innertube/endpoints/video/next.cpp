#include "next.h"
#include "innertube/innertubeexception.h"
#include "innertube/itc-objects/innertubeplaybackcontext.h"
#include <QJsonDocument>

namespace InnertubeEndpoints
{
    Next::Next(InnertubeContext* context, InnertubeAuthStore* authStore, const QString& videoId, const QString& tokenIn)
    {
        QJsonObject body;
        if (tokenIn.isEmpty())
        {
            body = {
                { "autonavState", "STATE_ON" },
                { "captionsRequested", false },
                { "contentCheckOk", false },
                { "context", context->toJson() },
                { "playbackContext", InnertubePlaybackContext().toJson() },
                { "racyCheckOk", false },
                { "videoId", videoId }
            };
        }
        else
        {
            body = {
                { "context", context->toJson() },
                { "continuation", tokenIn }
            };
        }

        QByteArray data = get(context, authStore, body);
        QJsonValue dataObj = QJsonDocument::fromJson(data).object();

        if (tokenIn.isEmpty())
        {
            QJsonValue watchNextResults = dataObj["contents"]["twoColumnWatchNextResults"];
            if (!watchNextResults.isObject())
                throw InnertubeException("[Next] twoColumnWatchNextResults is not an object");

            response.results = InnertubeObjects::TwoColumnWatchNextResults(watchNextResults);
            response.videoId = dataObj["currentVideoEndpoint"]["watchEndpoint"]["videoId"].toString();
        }
        else
        {
            QJsonValue onResponseReceivedEndpoints = dataObj["onResponseReceivedEndpoints"];
            if (!onResponseReceivedEndpoints.isArray())
                throw InnertubeException("[Next] onResponseReceivedEndpoints is not an array");
            response.continuationData.emplace(onResponseReceivedEndpoints);
        }
    }
}
