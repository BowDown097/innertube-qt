#ifndef ACCOUNTMENU_H
#define ACCOUNTMENU_H
#include "baseendpoint.h"
#include "itc-objects/innertubeauthstore.h"
#include <QJsonDocument>
#include <QNetworkReply>

namespace InnertubeEndpoints
{
    class AccountMenu : BaseEndpoint
    {
        friend class ::InnerTube;
    public:
        QString data;

        AccountMenu(InnertubeContext* context, QNetworkAccessManager* manager, InnertubeAuthStore* authStore)
        {
            QNetworkRequest request(QUrl("https://www.youtube.com/youtubei/v1/account/account_menu?key=AIzaSyAO_FJ2SlqU8Q4STEHLGCilw_Y9_11qcW8"));
            request.setRawHeader("Authorization", authStore->generateSAPISIDHash().toUtf8());
            request.setRawHeader("Cookie", authStore->getNecessaryLoginCookies().toUtf8());
            request.setRawHeader("X-Goog-AuthUser", "0");
            request.setRawHeader("X-Goog-Visitor-Id", context->client.visitorData.toLatin1());
            request.setRawHeader("X-YOUTUBE-CLIENT-NAME", context->client.clientName.toLatin1());
            request.setRawHeader("X-YOUTUBE-CLIENT-VERSION", context->client.clientVersion.toLatin1());
            request.setRawHeader("X-ORIGIN", "https://www.youtube.com");

            QJsonObject body = {
                { "context", context->toJson() },
                { "deviceTheme", "DEVICE_THEME_SUPPORTED" },
                { "userInterfaceTheme", context->client.userInterfaceTheme }
            };

            QNetworkReply* reply = manager->post(request, QJsonDocument(body).toJson());
            QEventLoop event;
            QObject::connect(reply, &QNetworkReply::finished, &event, &QEventLoop::quit);
            event.exec();

            data = reply->readAll();
        }
    };
}

#endif // ACCOUNTMENU_H
