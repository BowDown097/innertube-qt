#ifndef PLAYER_H
#define PLAYER_H
#include <endpoints/base/baseendpoint.h>
#include <itc-objects/innertubeauthstore.h>
#include <itc-objects/innertubeplaybackcontext.h>

namespace InnertubeEndpoints
{
    class Player : BaseEndpoint
    {
        friend class ::InnerTube;
    public:
        QString data;
    protected:
        explicit Player(const QString& videoId, InnertubeContext* context, QNetworkAccessManager* manager, InnertubeAuthStore* authStore)
        {
            QNetworkRequest request(QUrl("https://www.youtube.com/youtubei/v1/player?key=AIzaSyAO_FJ2SlqU8Q4STEHLGCilw_Y9_11qcW8&prettyPrint=false"));

            if (authStore->populated)
            {
                request.setRawHeader("Authorization", authStore->generateSAPISIDHash().toUtf8());
                request.setRawHeader("Cookie", authStore->getNecessaryLoginCookies().toUtf8());
                request.setRawHeader("X-Goog-AuthUser", "0");
            }

            request.setHeader(QNetworkRequest::ContentTypeHeader, "text/plain;charset=UTF-8");
            request.setRawHeader("X-Goog-Visitor-Id", context->client.visitorData.toLatin1());
            request.setRawHeader("X-YOUTUBE-CLIENT-NAME", context->client.clientName.toLatin1());
            request.setRawHeader("X-YOUTUBE-CLIENT-VERSION", context->client.clientVersion.toLatin1());
            request.setRawHeader("X-ORIGIN", "https://www.youtube.com");

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

            data = reply->readAll();
        }
    };
}


#endif // PLAYER_H
