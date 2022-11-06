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
            { "contentCheckOk", false },
            { "context", context->toJson() },
            { "playbackContext", InnertubePlaybackContext(true, QStringLiteral("/watch?v=%1").arg(videoId)).toJson() },
            { "racyCheckOk", false },
            { "videoId", videoId }
        };
        get("player", context, authStore, easy, body, data);

        QJsonObject dataObj = QJsonDocument::fromJson(data).object();
        QJsonObject playabilityObj = dataObj["playabilityStatus"].toObject();
        QString playabilityStatus = playabilityObj["status"].toString();
        if (playabilityStatus != "OK" && playabilityStatus != "LIVE_STREAM_OFFLINE" && playabilityStatus != "CONTENT_CHECK_REQUIRED")
        {
            QString errorReason = playabilityObj["reason"].toString();
            if (!errorReason.isEmpty())
                throw InnertubeException(QStringLiteral("[Player] Error: %1 - Playability status: %2").arg(errorReason, playabilityStatus));
            else
                throw InnertubeException(QStringLiteral("[Player] Playability status is %1 - no reason given.").arg(playabilityStatus));
        }

        response.playbackTracking = InnertubeObjects::PlaybackTracking(dataObj["playbackTracking"].toObject());
        response.streamingData = InnertubeObjects::StreamingData(dataObj["streamingData"].toObject());
        response.videoDetails = InnertubeObjects::PlayerVideoDetails(dataObj["videoDetails"].toObject());

        for (auto&& v : dataObj["captions"].toObject()["playerCaptionsTracklistRenderer"].toObject()["captionTracks"].toArray())
            response.captions.append(InnertubeObjects::CaptionTrack(v.toObject()));
    }
}
