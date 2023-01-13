#include "getnotificationmenu.h"
#include <QJsonArray>
#include <QJsonDocument>

namespace InnertubeEndpoints
{
    GetNotificationMenu::GetNotificationMenu(const QString& notificationsMenuRequestType, InnertubeContext* context, CurlEasy* easy,
                                             InnertubeAuthStore* authStore, const QString& tokenIn)
    {
        QJsonObject body = { { "context", context->toJson() } };
        if (tokenIn.isEmpty())
            body.insert("notificationsMenuRequestType", notificationsMenuRequestType);
        else
            body.insert("ctoken", tokenIn);

        QByteArray data;
        get("notification/get_notification_menu", context, authStore, easy, body, data);

        const QJsonObject action = QJsonDocument::fromJson(data).object()["actions"][0].toObject();
        if (action.contains("openPopupAction"))
        {
            QJsonValue menuRenderer = action["openPopupAction"]["popup"]["multiPageMenuRenderer"];
            response.headerTitle = menuRenderer["header"]["simpleMenuHeaderRenderer"]["title"]["simpleText"].toString();
            response.multiPageMenuStyle = menuRenderer["style"].toString();

            const QJsonArray items = menuRenderer["sections"][0]["multiPageMenuNotificationSectionRenderer"]["items"].toArray();
            for (const QJsonValue& v : items)
            {
                const QJsonObject o = v.toObject();
                if (o.contains("notificationRenderer"))
                    response.notifications.append(InnertubeObjects::Notification(v["notificationRenderer"]));
                else if (o.contains("continuationItemRenderer"))
                    continuationToken = v["continuationItemRenderer"]["continuationEndpoint"]["getNotificationMenuEndpoint"]["ctoken"].toString();
            }
        }
        else if (action.contains("appendContinuationItemsAction"))
        {
            const QJsonArray continuationItems = action["appendContinuationItemsAction"]["continuationItems"].toArray();
            for (const QJsonValue& v : continuationItems)
            {
                const QJsonObject o = v.toObject();
                if (o.contains("notificationRenderer"))
                    response.notifications.append(InnertubeObjects::Notification(v["notificationRenderer"]));
                else if (o.contains("continuationItemRenderer"))
                    continuationToken = v["continuationItemRenderer"]["continuationEndpoint"]["getNotificationMenuEndpoint"]["ctoken"].toString();
            }
        }
    }
}
