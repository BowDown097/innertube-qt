#ifndef NOTIFICATIONPREFERENCEBUTTON_H
#define NOTIFICATIONPREFERENCEBUTTON_H
#include "innertube/objects/items/menuserviceitem.h"
#include "notificationstate.h"

namespace InnertubeObjects
{
    class NotificationPreferenceButton
    {
    public:
        int currentStateId = 0;
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
