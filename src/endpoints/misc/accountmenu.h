#ifndef ACCOUNTMENU_H
#define ACCOUNTMENU_H
#include <endpoints/base/baseendpoint.h>

namespace InnertubeEndpoints
{
    class AccountMenu : BaseEndpoint
    {
        friend class ::InnerTube;
    private:
        AccountMenu(InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore)
        {
            easy->set(CURLOPT_URL, "https://www.youtube.com/youtubei/v1/account/account_menu?key=AIzaSyAO_FJ2SlqU8Q4STEHLGCilw_Y9_11qcW8&prettyPrint=false");
            setNeededHeaders(easy, context, authStore);

            QJsonObject body = {
                { "context", context->toJson() },
                { "deviceTheme", "DEVICE_THEME_SUPPORTED" },
                { "userInterfaceTheme", context->client.userInterfaceTheme }
            };

            QByteArray data;
            getData(easy, body, data);
        }
    };
}

#endif // ACCOUNTMENU_H
