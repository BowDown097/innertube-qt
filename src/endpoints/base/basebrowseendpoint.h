#ifndef BASEBROWSEENDPOINT_H
#define BASEBROWSEENDPOINT_H
#include "baseendpoint.h"

namespace InnertubeEndpoints
{
    class BaseBrowseEndpoint : public BaseEndpoint
    {
    protected:
        QString data;
        explicit BaseBrowseEndpoint(const QString& browseId, InnertubeContext* context, QNetworkAccessManager* manager, InnertubeAuthStore* authStore)
        {
            QNetworkRequest request(QUrl("https://www.youtube.com/youtubei/v1/browse?key=AIzaSyAO_FJ2SlqU8Q4STEHLGCilw_Y9_11qcW8&prettyPrint=false"));
            setNeededHeaders(request, context, authStore);

            QJsonObject body = {
                { "context", context->toJson() },
                { "browseId", browseId }
            };

            QNetworkReply* reply = manager->post(request, QJsonDocument(body).toJson());
            QEventLoop event;
            QObject::connect(reply, &QNetworkReply::finished, &event, &QEventLoop::quit);
            event.exec();

            data = reply->readAll();
        }
    };
}

#endif // BASEBROWSEENDPOINT_H
