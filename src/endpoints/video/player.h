#ifndef PLAYER_H
#define PLAYER_H
#include <endpoints/base/baseendpoint.h>
#include <itc-objects/innertubeplaybackcontext.h>

namespace InnertubeEndpoints
{
    class Player : BaseEndpoint
    {
        friend class ::InnerTube;
    private:
        explicit Player(const QString& videoId, InnertubeContext* context, QNetworkAccessManager* manager, InnertubeAuthStore* authStore)
        {
            QNetworkRequest request(QUrl("https://www.youtube.com/youtubei/v1/player?key=AIzaSyAO_FJ2SlqU8Q4STEHLGCilw_Y9_11qcW8&prettyPrint=false"));
            setNeededHeaders(request, context, authStore);

            QJsonObject body = {
                { "contentCheckOk", false },
                { "context", context->toJson() },
                { "playbackContext", InnertubePlaybackContext(true, QStringLiteral("/watch?v=%1").arg(videoId)).toJson() },
                { "racyCheckOk", false },
                { "videoId", videoId }
            };

            QNetworkReply* reply = manager->post(request, QJsonDocument(body).toJson());
            QEventLoop event;
            QObject::connect(reply, &QNetworkReply::finished, &event, &QEventLoop::quit);
            event.exec();
        }
    };
}


#endif // PLAYER_H
