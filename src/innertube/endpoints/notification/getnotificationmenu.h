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
        GetNotificationMenu(InnertubeContext* context, InnertubeAuthStore* authStore,
                            const QString& notificationsMenuRequestType, const QString& tokenIn = "");
    };
}
