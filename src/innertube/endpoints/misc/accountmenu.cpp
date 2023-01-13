#include "accountmenu.h"

namespace InnertubeEndpoints
{
    AccountMenu::AccountMenu(InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore)
    {
        QByteArray data;
        const QJsonObject body {
            { "context", context->toJson() },
            { "deviceTheme", "DEVICE_THEME_SUPPORTED" },
            { "userInterfaceTheme", context->client.userInterfaceTheme }
        };
        get("account/account_menu", context, authStore, easy, body, data);
    }
}
