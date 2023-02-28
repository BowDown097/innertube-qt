#include "accountmenu.h"

namespace InnertubeEndpoints
{
    AccountMenu::AccountMenu(InnertubeContext* context, InnertubeAuthStore* authStore)
    {
        Q_UNUSED(context);
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
