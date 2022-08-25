#ifndef NEXT_H
#define NEXT_H
#include <endpoints/base/baseendpoint.h>
#include <itc-objects/innertubeplaybackcontext.h>

namespace InnertubeEndpoints
{
    class NextVideo : BaseEndpoint
    {
        friend class ::InnerTube;
    private:
        explicit NextVideo(const QString& videoId, InnertubeContext* context, QNetworkAccessManager* manager, InnertubeAuthStore* authStore)
        {
            QNetworkRequest request(QUrl("https://www.youtube.com/youtubei/v1/next?key=AIzaSyAO_FJ2SlqU8Q4STEHLGCilw_Y9_11qcW8&prettyPrint=false"));
            setNeededHeaders(request, context, authStore);

            QJsonObject body = {
                { "autonavState", "STATE_ON" },
                { "captionsRequested", false },
                { "contentCheckOk", false },
                { "context", context->toJson() },
                { "playbackContext", InnertubePlaybackContext(false, "").toJson() },
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

#endif // NEXT_H
