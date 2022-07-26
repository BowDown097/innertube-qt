#include "next.h"
#include "innertube/innertubeexception.h"
#include "innertube/itc-objects/innertubeplaybackcontext.h"
#include <QJsonArray>
#include <QJsonDocument>

namespace InnertubeEndpoints
{
    Next::Next(const QString& videoId, InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore, const QString& tokenIn)
    {
        QByteArray data;
        QJsonObject body = {
            { "autonavState", "STATE_ON" },
            { "captionsRequested", false },
            { "contentCheckOk", false },
            { "context", context->toJson() },
            { "playbackContext", InnertubePlaybackContext(false, "").toJson() },
            { "racyCheckOk", false },
            { "videoId", videoId }
        };
        get("next", context, authStore, easy, body, data);

        QJsonValue dataObj = QJsonDocument::fromJson(data).object();
        if (tokenIn.isEmpty())
        {
            QJsonArray watchNextContents = dataObj["contents"]["twoColumnWatchNextResults"]["results"]["results"]["contents"].toArray();
            if (watchNextContents.isEmpty())
                throw InnertubeException("[Next] watchNextResults not found or is empty");

            response.primaryInfo = InnertubeObjects::VideoPrimaryInfo(watchNextContents[0].toObject()["videoPrimaryInfoRenderer"]);
            response.secondaryInfo = InnertubeObjects::VideoSecondaryInfo(watchNextContents[1].toObject()["videoSecondaryInfoRenderer"]);
        }
        // TODO: comments (and thus continuations)
    }
}
