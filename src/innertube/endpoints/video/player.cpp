#include "player.h"
#include "innertube/innertubeexception.h"
#include "innertube/itc-objects/innertubeplaybackcontext.h"
#include <QJsonArray>
#include <QJsonDocument>

namespace InnertubeEndpoints
{
    Player::Player(InnertubeContext* context, InnertubeAuthStore* authStore, const QString& videoId)
    {
        QJsonObject body {
            { "contentCheckOk", true },
            { "context", context->toJson() },
            { "playbackContext", InnertubePlaybackContext(true, QStringLiteral("/watch?v=%1").arg(videoId)).toJson() },
            { "racyCheckOk", true },
            { "videoId", videoId }
        };

        // streaming urls return 403 on ANDROID client without a "params" argument
        // so we work around this by using a random but authentic value for the argument
        // courtesy of NewPipe's YoutubeStreamExtractor.fetchAndroidMobileJsonPlayer()
        if (context->client.clientType == InnertubeClient::ClientType::ANDROID)
            body.insert("params", "CgIQBg");

        QByteArray data = get(context, authStore, body);
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
