#ifndef NOTIFICATIONPREFERENCEBUTTON_H
#define NOTIFICATIONPREFERENCEBUTTON_H
#include "innertube/objects/items/menuserviceitem.h"
#include "notificationstate.h"

namespace InnertubeObjects
{
    struct NotificationPreferenceButton
    {
        int currentStateId;
        QString secondaryIconType;
        QList<MenuServiceItem> services;
        QList<NotificationState> states;
        QString targetId;

        NotificationPreferenceButton() = default;
        explicit NotificationPreferenceButton(const QJsonValue& notificationToggleButtonRenderer);

        NotificationState getCurrentState() const;
        MenuServiceItem getService(const QString& iconType) const;
    };
}

#endif // NOTIFICATIONPREFERENCEBUTTON_H
