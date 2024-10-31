#pragma once
#include "innertube/objects/items/menu/menu.h"
#include "notificationstate.h"

namespace InnertubeObjects
{
    struct NotificationPreferenceButton
    {
        int currentStateId{};
        Menu popup;
        QString secondaryIconType;
        QList<NotificationState> states;
        QString targetId;

        NotificationPreferenceButton() = default;
        explicit NotificationPreferenceButton(const QJsonValue& notificationToggleButtonRenderer);

        const NotificationState* getCurrentState() const;
        const MenuServiceItem* getService(const QString& iconType) const;
    };
}
