#include "accountmenu.h"

namespace InnertubeEndpoints
{
    AccountMenu::AccountMenu(InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore)
    {
        Q_UNUSED(context);
        Q_UNUSED(easy);
        Q_UNUSED(authStore);
        /*
        const QJsonObject body {
            { "context", context->toJson() },
            { "deviceTheme", "DEVICE_THEME_SUPPORTED" },
            { "userInterfaceTheme", context->client.userInterfaceTheme }
        };

        QByteArray data = get("account/account_menu", context, authStore, easy, body);
        QJsonValue dataObj = QJsonDocument::fromJson(data).object();
        */
    }
}
