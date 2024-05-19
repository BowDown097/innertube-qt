#include "getnotificationmenu.h"
#include <QJsonArray>

namespace InnertubeEndpoints
{
    GetNotificationMenu::GetNotificationMenu(InnertubeContext* context, InnertubeAuthStore* authStore,
                                             const QString& notificationsMenuRequestType, const QString& tokenIn)
    {
        QJsonObject body = { EndpointMethods::contextPair(context) };
        if (tokenIn.isEmpty())
            body.insert("notificationsMenuRequestType", notificationsMenuRequestType);
        else
            body.insert("ctoken", tokenIn);

        const QJsonValue data = get(context, authStore, body);
        const QJsonValue action = data["actions"][0];

        if (action["openPopupAction"].isObject())
        {
            const QJsonValue menuRenderer = action["openPopupAction"]["popup"]["multiPageMenuRenderer"];
            response.headerTitle = menuRenderer["header"]["simpleMenuHeaderRenderer"]["title"]["simpleText"].toString();
            response.multiPageMenuStyle = menuRenderer["style"].toString();

            const QJsonArray items = menuRenderer["sections"][0]["multiPageMenuNotificationSectionRenderer"]["items"].toArray();
            for (const QJsonValue& v : items)
            {
                if (v["notificationRenderer"].isObject())
                    response.notifications.append(InnertubeObjects::Notification(v["notificationRenderer"]));
                else if (v["continuationItemRenderer"].isObject())
                    continuationToken = v["continuationItemRenderer"]["continuationEndpoint"]["getNotificationMenuEndpoint"]["ctoken"].toString();
            }
        }
        else if (action["appendContinuationItemsAction"].isObject())
        {
            const QJsonArray continuationItems = action["appendContinuationItemsAction"]["continuationItems"].toArray();
            for (const QJsonValue& v : continuationItems)
            {
                if (v["notificationRenderer"].isObject())
                    response.notifications.append(InnertubeObjects::Notification(v["notificationRenderer"]));
                else if (v["continuationItemRenderer"].isObject())
                    continuationToken = v["continuationItemRenderer"]["continuationEndpoint"]["getNotificationMenuEndpoint"]["ctoken"].toString();
            }
        }
    }
}
