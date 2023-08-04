#include "notificationpreferencebutton.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    NotificationPreferenceButton::NotificationPreferenceButton(const QJsonValue& notificationToggleButtonRenderer)
        : currentStateId(notificationToggleButtonRenderer["currentStateId"].toInt()),
          secondaryIconType(notificationToggleButtonRenderer["secondaryIcon"]["iconType"].toString()),
          targetId(notificationToggleButtonRenderer["targetId"].toString())
    {
        const QJsonArray servicesJson = notificationToggleButtonRenderer["command"]["commandExecutorCommand"]["commands"]
                [0]["openPopupAction"]["popup"]["menuPopupRenderer"]["items"].toArray();
        for (const QJsonValue& v : servicesJson)
            services.append(MenuServiceItem(v["menuServiceItemRenderer"]));

        const QJsonArray statesJson = notificationToggleButtonRenderer["states"].toArray();
        for (const QJsonValue& v : statesJson)
            states.append(NotificationState(v));
    }

    NotificationState NotificationPreferenceButton::getCurrentState() const
    {
        auto it = std::ranges::find_if(states, [this](const NotificationState& ns) { return ns.stateId == currentStateId; });
        return it != states.end() ? *it : NotificationState();
    }

    MenuServiceItem NotificationPreferenceButton::getService(const QString& iconType) const
    {
        auto it = std::ranges::find_if(services, [iconType](const MenuServiceItem& msi) { return msi.iconType == iconType; });
        return it != services.end() ? *it : MenuServiceItem();
    }
}
