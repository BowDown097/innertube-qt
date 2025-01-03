#include "getnotificationmenu.h"
#include <QJsonArray>

namespace InnertubeEndpoints
{
    GetNotificationMenu::GetNotificationMenu(const InnertubeContext* context, const InnertubeAuthStore* authStore,
                                             const QString& notificationsMenuRequestType, const QString& tokenIn)
        : GetNotificationMenu(get(context, authStore, createBody(context, notificationsMenuRequestType, tokenIn))) {}

    GetNotificationMenu::GetNotificationMenu(const QJsonValue& data)
    {
        QJsonArray items;

        const QJsonValue action = data["actions"][0];
        if (const QJsonValue openPopup = action["openPopupAction"]; openPopup.isObject())
        {
            const QJsonValue menuRenderer = openPopup["popup"]["multiPageMenuRenderer"];
            response.headerTitle = menuRenderer["header"]["simpleMenuHeaderRenderer"]["title"]["simpleText"].toString();
            response.multiPageMenuStyle = menuRenderer["style"].toString();

            items = menuRenderer["sections"][0]["multiPageMenuNotificationSectionRenderer"]["items"].toArray();
        }
        else if (const QJsonValue appendContinuationItems = action["appendContinuationItemsAction"];
                 appendContinuationItems.isObject())
        {
            items = appendContinuationItems["continuationItems"].toArray();
        }

        for (const QJsonValue& v : std::as_const(items))
        {
            if (const QJsonValue notification = v["notificationRenderer"]; notification.isObject())
                response.notifications.append(InnertubeObjects::Notification(notification));
            else if (const QJsonValue continuation = v["continuationItemRenderer"]; continuation.isObject())
                continuationToken = continuation["continuationEndpoint"]["getNotificationMenuEndpoint"]["ctoken"].toString();
        }
    }

    QJsonObject GetNotificationMenu::createBody(const InnertubeContext* context,
        const QString& notificationsMenuRequestType, const QString& tokenIn)
    {
        QJsonObject body = { { "context", context->toJson() } };
        if (tokenIn.isEmpty())
            body.insert("notificationsMenuRequestType", notificationsMenuRequestType);
        else
            body.insert("ctoken", tokenIn);

        return body;
    }
}
