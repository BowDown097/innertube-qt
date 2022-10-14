#include "next.h"
#include "innertube/itc-objects/innertubeplaybackcontext.h"
#include <QJsonDocument>

namespace InnertubeEndpoints
{
    Next::Next(const QString& videoId, InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore)
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
    }
}
