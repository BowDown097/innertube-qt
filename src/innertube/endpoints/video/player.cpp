#include "player.h"
#include "innertube/innertubeexception.h"
#include "innertube/itc-objects/innertubeplaybackcontext.h"
#include <QJsonArray>
#include <QJsonDocument>

namespace InnertubeEndpoints
{
    Player::Player(const QString& videoId, InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore)
    {
        QByteArray data;
        QJsonObject body = {
            { "contentCheckOk", true },
            { "context", context->toJson() },
            { "playbackContext", InnertubePlaybackContext(true, QStringLiteral("/watch?v=%1").arg(videoId)).toJson() },
            { "racyCheckOk", true },
            { "videoId", videoId }
        };
        get("player", context, authStore, easy, body, data);

        QJsonValue dataObj = QJsonDocument::fromJson(data).object();
        QString playabilityStatus = dataObj["playabilityStatus"]["status"].toString();
        if (playabilityStatus != "OK" && playabilityStatus != "LIVE_STREAM_OFFLINE" && playabilityStatus != "CONTENT_CHECK_REQUIRED")
        {
            QString errorReason = dataObj["playabilityStatus"]["reason"].toString();
            if (!errorReason.isEmpty())
                throw InnertubeException(QStringLiteral("[Player] Error: %1 - Playability status: %2").arg(errorReason, playabilityStatus));
            else
                throw InnertubeException(QStringLiteral("[Player] Playability status is %1 - no reason given.").arg(playabilityStatus));
        }

        response.playbackTracking = InnertubeObjects::PlaybackTracking(dataObj["playbackTracking"]);
        response.streamingData = InnertubeObjects::StreamingData(dataObj["streamingData"]);
        response.videoDetails = InnertubeObjects::PlayerVideoDetails(dataObj["videoDetails"]);

        const QJsonArray captionTracks = dataObj["captions"]["playerCaptionsTracklistRenderer"]["captionTracks"].toArray();
        for (const QJsonValue& v : captionTracks)
            response.captions.append(InnertubeObjects::CaptionTrack(v));
    }
}
