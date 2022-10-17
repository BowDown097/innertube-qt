#include "next.h"
#include "innertube/innertubeexception.h"
#include "innertube/itc-objects/innertubeplaybackcontext.h"
#include <QJsonArray>
#include <QJsonDocument>

namespace InnertubeEndpoints
{
    Next::Next(const QString& videoId, InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore, const QString& tokenIn)
    {
        easy->set(CURLOPT_URL, "https://www.youtube.com/youtubei/v1/next?key=AIzaSyAO_FJ2SlqU8Q4STEHLGCilw_Y9_11qcW8&prettyPrint=false");
        setNeededHeaders(easy, context, authStore);

        QJsonObject body = {
            { "autonavState", "STATE_ON" },
            { "captionsRequested", false },
            { "contentCheckOk", false },
            { "context", context->toJson() },
            { "playbackContext", InnertubePlaybackContext(false, "").toJson() },
            { "racyCheckOk", false },
            { "videoId", videoId }
        };

        QByteArray data;
        getData(easy, body, data);

        QJsonObject dataObj = QJsonDocument::fromJson(data).object();
        if (tokenIn.isEmpty())
        {
            QJsonObject watchNextResults = dataObj["contents"].toObject()["twoColumnWatchNextResults"].toObject();
            if (watchNextResults.isEmpty())
                throw InnertubeException("[Next] watchNextResults not found or is empty");

            QJsonArray resultContents = watchNextResults["results"].toObject()["results"].toObject()["contents"].toArray();
            if (resultContents.isEmpty())
                throw InnertubeException("[Next] watchNextResults has no contents");

            primaryInfo = InnertubeObjects::VideoPrimaryInfo(resultContents[0].toObject()["videoPrimaryInfoRenderer"]);
            secondaryInfo = InnertubeObjects::VideoSecondaryInfo(resultContents[1].toObject()["videoSecondaryInfoRenderer"]);
        }
        // TODO: comments (and thus continuations)
    }
}
