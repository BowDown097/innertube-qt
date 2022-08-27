#ifndef ACCOUNTMENU_H
#define ACCOUNTMENU_H
#include "base/baseendpoint.h"

namespace InnertubeEndpoints
{
    class AccountMenu : BaseEndpoint
    {
        friend class ::InnerTube;
    private:
        explicit AccountMenu(InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore)
        {
            easy->set(CURLOPT_URL, "https://www.youtube.com/youtubei/v1/account/account_menu?key=AIzaSyAO_FJ2SlqU8Q4STEHLGCilw_Y9_11qcW8&prettyPrint=false");
            setNeededHeaders(easy, context, authStore);

            QJsonObject body = {
                { "context", context->toJson() },
                { "deviceTheme", "DEVICE_THEME_SUPPORTED" },
                { "userInterfaceTheme", context->client.userInterfaceTheme }
            };

            QByteArray data;
            QByteArray bodyBytes = QJsonDocument(body).toJson(QJsonDocument::Compact);
            easy->set(CURLOPT_POSTFIELDS, bodyBytes.constData());
            easy->set(CURLOPT_VERBOSE, 1L);
            easy->setWriteFunction([&data](char* d, size_t size)->size_t {
               data.append(d);
               return size;
            });

            easy->perform();
            QEventLoop event;
            QObject::connect(easy, &CurlEasy::done, &event, &QEventLoop::quit);
            event.exec();
        }
    };
}

#endif // ACCOUNTMENU_H
