#ifndef PLAYER_H
#define PLAYER_H
#include <endpoints/base/baseendpoint.h>
#include <itc-objects/innertubeplaybackcontext.h>
#include <objects/player/captiontrack.h>
#include <objects/player/playbacktracking.h>
#include <objects/player/playervideodetails.h>
#include <objects/player/streamingdata.h>

namespace InnertubeEndpoints
{
    class Player : BaseEndpoint
    {
        friend class ::InnerTube;
    public:
        QList<InnertubeObjects::CaptionTrack> captions;
        InnertubeObjects::PlaybackTracking playbackTracking;
        InnertubeObjects::StreamingData streamingData;
        InnertubeObjects::PlayerVideoDetails videoDetails;
    private:
        explicit Player(const QString& videoId, InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore)
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
            if (playabilityStatus != "OK")
            {
                QString errorReason = playabilityObj["reason"].toString();
                if (!errorReason.isEmpty())
                    throw InnertubeException("[Player] Error: " + errorReason);
                else
                    throw InnertubeException(QStringLiteral("[Player] Playability status is %1 - no reason given.").arg(playabilityStatus));
            }

            playbackTracking = InnertubeObjects::PlaybackTracking(dataObj["playbackTracking"].toObject());
            streamingData = InnertubeObjects::StreamingData(dataObj["streamingData"].toObject());
            videoDetails = InnertubeObjects::PlayerVideoDetails(dataObj["videoDetails"].toObject());

            for (auto&& v : dataObj["captions"].toObject()["playerCaptionsTracklistRenderer"].toObject()["captionTracks"].toArray())
                captions.append(InnertubeObjects::CaptionTrack(v.toObject()));
        }
    };
}


#endif // PLAYER_H
