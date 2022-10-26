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

        QJsonObject dataObj = QJsonDocument::fromJson(data).object();
        if (tokenIn.isEmpty())
        {
            QJsonObject watchNextResults = dataObj["contents"].toObject()["twoColumnWatchNextResults"].toObject();
            if (watchNextResults.isEmpty())
                throw InnertubeException("[Next] watchNextResults not found or is empty");

            QJsonArray resultContents = watchNextResults["results"].toObject()["results"].toObject()["contents"].toArray();
            if (resultContents.isEmpty())
                throw InnertubeException("[Next] watchNextResults has no contents");

            response.primaryInfo = InnertubeObjects::VideoPrimaryInfo(resultContents[0].toObject()["videoPrimaryInfoRenderer"]);
            response.secondaryInfo = InnertubeObjects::VideoSecondaryInfo(resultContents[1].toObject()["videoSecondaryInfoRenderer"]);
        }
        // TODO: comments (and thus continuations)
    }
}
