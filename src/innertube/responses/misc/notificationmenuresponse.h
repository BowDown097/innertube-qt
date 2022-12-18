#ifndef NOTIFICATIONMENURESPONSE_H
#define NOTIFICATIONMENURESPONSE_H
#include "innertube/objects/notification/notification.h"

namespace InnertubeEndpoints
{
    struct NotificationMenuResponse
    {
        QString headerTitle; // this will not exist if response is from a continuation
        QString multiPageMenuStyle; // this will not exist if response is from a continuation
        QList<InnertubeObjects::Notification> notifications;
    };
}

#endif // NOTIFICATIONMENURESPONSE_H
