#ifndef GETNOTIFICATIONMENU_H
#define GETNOTIFICATIONMENU_H
#include "innertube/endpoints/base/baseendpoint.h"
#include "innertube/responses/misc/notificationmenuresponse.h"

namespace InnertubeEndpoints
{
    /**
     * @brief Notifications.
     */
    class GetNotificationMenu : public BaseEndpoint
    {
        friend class ::InnerTube;
    public:
        QString continuationToken;
        NotificationMenuResponse response;
    protected:
        /**
         * @param tokenIn  Continuation token.
         */
        GetNotificationMenu(const QString& notificationsMenuRequestType, InnertubeContext* context,
                            InnertubeAuthStore* authStore, const QString& tokenIn = "");
    };
}

#endif // GETNOTIFICATIONMENU_H
