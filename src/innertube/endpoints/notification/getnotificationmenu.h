#pragma once
#include "innertube/endpoints/base/baseendpoint.h"
#include "innertube/responses/notification/notificationmenuresponse.h"

namespace InnertubeEndpoints
{
    /**
     * @brief Notifications.
     */
    struct GetNotificationMenu : BaseEndpoint<"notification/get_notification_menu">
    {
        QString continuationToken;
        NotificationMenuResponse response;

        explicit GetNotificationMenu(const QJsonValue& data);
        static QJsonObject createBody(
            const InnertubeContext* context, const QString& notificationsMenuRequestType,
            const QString& continuationToken = "");
    };
}
