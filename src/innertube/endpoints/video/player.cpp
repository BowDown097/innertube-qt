#include "player.h"
#include "innertube/innertubeexception.h"
#include "innertube/itc-objects/innertubeplaybackcontext.h"
#include <QJsonArray>
#include <QJsonDocument>

namespace InnertubeEndpoints
{
    Player::Player(const QString& videoId, InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore)
    {
        easy->set(CURLOPT_URL, "https://www.youtube.com/youtubei/v1/player?key=AIzaSyAO_FJ2SlqU8Q4STEHLGCilw_Y9_11qcW8&prettyPrint=false");
        setNeededHeaders(easy, context, authStore);

        QJsonObject body = {
            { "contentCheckOk", false },
            { "context", context->toJson() },
            { "playbackContext", InnertubePlaybackContext(true, QStringLiteral("/watch?v=%1").arg(videoId)).toJson() },
            { "racyCheckOk", false },
            { "videoId", videoId }
        };

        QByteArray data;
        getData(easy, body, data);
        QJsonObject dataObj = QJsonDocument::fromJson(data).object();

        QJsonObject playabilityObj = dataObj["playabilityStatus"].toObject();
        QString playabilityStatus = playabilityObj["status"].toString();
        if (playabilityStatus != "OK" && playabilityStatus != "LIVE_STREAM_OFFLINE")
        {
            QString errorReason = playabilityObj["reason"].toString();
            if (!errorReason.isEmpty())
                throw InnertubeException(QStringLiteral("[Player] Error: %1 - Playability status: %2").arg(errorReason, playabilityStatus));
            else
                throw InnertubeException(QStringLiteral("[Player] Playability status is %1 - no reason given.").arg(playabilityStatus));
        }

        playbackTracking = InnertubeObjects::PlaybackTracking(dataObj["playbackTracking"].toObject());
        streamingData = InnertubeObjects::StreamingData(dataObj["streamingData"].toObject());
        videoDetails = InnertubeObjects::PlayerVideoDetails(dataObj["videoDetails"].toObject());

        for (auto&& v : dataObj["captions"].toObject()["playerCaptionsTracklistRenderer"].toObject()["captionTracks"].toArray())
            captions.append(InnertubeObjects::CaptionTrack(v.toObject()));
    }
}
