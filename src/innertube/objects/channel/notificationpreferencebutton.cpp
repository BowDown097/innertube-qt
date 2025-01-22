#include "notificationpreferencebutton.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    NotificationPreferenceButton::NotificationPreferenceButton(const QJsonValue& notificationToggleButtonRenderer)
        : currentStateId(notificationToggleButtonRenderer["currentStateId"].toInt()),
          popup(notificationToggleButtonRenderer["command"]["commandExecutorCommand"]["commands"][0]
                                                ["openPopupAction"]["popup"]["menuPopupRenderer"]),
          secondaryIconType(notificationToggleButtonRenderer["secondaryIcon"]["iconType"].toString()),
          targetId(notificationToggleButtonRenderer["targetId"].toString())
    {
        const QJsonArray statesJson = notificationToggleButtonRenderer["states"].toArray();
        for (const QJsonValue& v : statesJson)
            states.append(NotificationState(v));
    }

    const NotificationState* NotificationPreferenceButton::getCurrentState() const
    {
        auto it = std::ranges::find(states, currentStateId, &NotificationState::stateId);
        return it != states.end() ? &(*it) : nullptr;
    }

    const MenuServiceItem* NotificationPreferenceButton::getService(const QString& iconType) const
    {
        auto it = std::ranges::find(popup.items, iconType, &MenuServiceItem::iconType);
        return it != popup.items.end() ? &(*it) : nullptr;
    }
}
