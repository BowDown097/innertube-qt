#ifndef ACCOUNTMENU_H
#define ACCOUNTMENU_H
#include "base/baseendpoint.h"

namespace InnertubeEndpoints
{
    class AccountMenu : BaseEndpoint
    {
        friend class ::InnerTube;
    private:
        explicit AccountMenu(InnertubeContext* context, QNetworkAccessManager* manager, InnertubeAuthStore* authStore)
        {
            QNetworkRequest request(QUrl("https://www.youtube.com/youtubei/v1/account/account_menu?key=AIzaSyAO_FJ2SlqU8Q4STEHLGCilw_Y9_11qcW8&prettyPrint=false"));
            setNeededHeaders(request, context, authStore);

            QJsonObject body = {
                { "context", context->toJson() },
                { "deviceTheme", "DEVICE_THEME_SUPPORTED" },
                { "userInterfaceTheme", context->client.userInterfaceTheme }
            };

            QNetworkReply* reply = manager->post(request, QJsonDocument(body).toJson());
            QEventLoop event;
            QObject::connect(reply, &QNetworkReply::finished, &event, &QEventLoop::quit);
            event.exec();
        }
    };
}

#endif // ACCOUNTMENU_H
