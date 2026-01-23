#include "player.h"
#include "innertube/innertubeexception.h"
#include "innertube/itc-objects/innertubecontext.h"
#include "innertube/itc-objects/innertubeplaybackcontext.h"
#include <QJsonArray>

namespace InnertubeEndpoints
{
    Player::Player(const QJsonValue& data)
    {
        const QJsonValue playabilityStatus = data["playabilityStatus"];
        const QString status = playabilityStatus["status"].toString();
        static QStringList noErrorStatuses = { "OK", "LIVE_STREAM_OFFLINE", "CONTENT_CHECK_REQUIRED" };

        if (!noErrorStatuses.contains(status))
        {
            // TODO: investigate this reload error further to find an actual fix.
            // QtTube is just wrapping around the web player, and on that, this error does not happen somehow.
            const QString errorReason = fetchErrorReason(playabilityStatus, status);
            if (errorReason != "The page needs to be reloaded.")
            {
                if (!errorReason.isEmpty())
                    throw InnertubeException(QStringLiteral("[Player] Error: %1 (%2)").arg(errorReason, status));
                else
                    throw InnertubeException(QStringLiteral("[Player] Video is %1 - no reason given.").arg(status));
            }
        }

        response.playbackTracking = InnertubeObjects::PlaybackTracking(data["playbackTracking"]);
        response.streamingData = InnertubeObjects::StreamingData(data["streamingData"]);
        response.videoDetails = InnertubeObjects::PlayerVideoDetails(data["videoDetails"]);

        const QJsonArray captionTracks = data["captions"]["playerCaptionsTracklistRenderer"]["captionTracks"].toArray();
        for (const QJsonValue& v : captionTracks)
            response.captions.append(InnertubeObjects::CaptionTrack(v));
    }

    QJsonObject Player::createBody(const InnertubeContext* context, const QString& videoId, const QString& poToken)
    {
        QJsonObject body = {
            { "contentCheckOk", true },
            { "context", context->toJson() },
            { "playbackContext", InnertubePlaybackContext(true, QStringLiteral("/watch?v=%1").arg(videoId)).toJson() },
            { "racyCheckOk", true },
            { "videoId", videoId }
        };

        if (!poToken.isEmpty())
            body.insert("serviceIntegrityDimensions", { { "poToken", poToken } });

        // streaming urls return 403 on ANDROID client without a "params" argument
        // so we work around this by using a random but authentic value for the argument
        // courtesy of NewPipe's YoutubeStreamExtractor.fetchAndroidMobileJsonPlayer()
        if (context->client.clientType == InnertubeClient::ClientType::ANDROID)
            body.insert("params", "CgIQBg");

        return body;
    }

    QString Player::fetchErrorReason(const QJsonValue& playabilityStatus, const QString& status)
    {
        if (status == "UNPLAYABLE")
        {
            InnertubeObjects::InnertubeString reason(
                playabilityStatus["errorScreen"]["playerErrorMessageRenderer"]["reason"]);
            if (!reason.text.isEmpty())
                return reason.text;
        }

        return playabilityStatus["reason"].toString();
    }
}
