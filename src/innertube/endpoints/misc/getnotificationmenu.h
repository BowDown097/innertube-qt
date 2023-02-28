#ifndef GETNOTIFICATIONMENU_H
#define GETNOTIFICATIONMENU_H
#include "innertube/endpoints/base/baseendpoint.h"
#include "innertube/responses/misc/notificationmenuresponse.h"

namespace InnertubeEndpoints
{
    class GetNotificationMenu : public BaseEndpoint
    {
        friend class ::InnerTube;
    public:
        QString continuationToken;
        NotificationMenuResponse response;
    private:
        GetNotificationMenu(const QString& notificationsMenuRequestType, InnertubeContext* context, InnertubeAuthStore* authStore,
                            const QString& tokenIn = "");
    };
}

#endif // GETNOTIFICATIONMENU_H
