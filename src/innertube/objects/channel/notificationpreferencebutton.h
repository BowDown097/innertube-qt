#ifndef NOTIFICATIONPREFERENCEBUTTON_H
#define NOTIFICATIONPREFERENCEBUTTON_H
#include "innertube/objects/items/menuserviceitem.h"
#include "notificationstate.h"

namespace InnertubeObjects
{
    class NotificationPreferenceButton
    {
    public:
        int currentStateId;
        QString secondaryIconType;
        QList<MenuServiceItem> services;
        QList<NotificationState> states;
        QString targetId;

        NotificationPreferenceButton() = default;
        explicit NotificationPreferenceButton(const QJsonValue& notificationToggleButtonRenderer);
        const NotificationState& getCurrentState() const;
        const MenuServiceItem& getService(const QString& iconType) const;
    };
}

#endif // NOTIFICATIONPREFERENCEBUTTON_H