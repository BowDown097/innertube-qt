#pragma once
#include "innertube/endpoints/base/baseendpoint.h"
#include "innertube/responses/notification/notificationmenuresponse.h"

namespace InnertubeEndpoints
{
    /**
     * @brief Notifications.
     */
    class GetNotificationMenu : public BaseEndpoint<"notification/get_notification_menu">
    {
        friend class ::InnerTube;
    public:
        QString continuationToken;
        NotificationMenuResponse response;
    protected:
        /**
         * @param tokenIn  Continuation token.
         */
        GetNotificationMenu(const InnertubeContext* context, const InnertubeAuthStore* authStore,
                            const QString& notificationsMenuRequestType, const QString& tokenIn = "");

        explicit GetNotificationMenu(const QJsonValue& data);
    private:
        static QJsonObject createBody(const InnertubeContext* context,
            const QString& notificationsMenuRequestType, const QString& tokenIn);
    };
}
