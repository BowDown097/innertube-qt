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

    const NotificationState& NotificationPreferenceButton::getCurrentState() const
    {
        return *std::find_if(states.cbegin(), states.cend(), [this](const NotificationState& ns) { return ns.stateId == currentStateId; });
    }

    const MenuServiceItem& NotificationPreferenceButton::getService(const QString& iconType) const
    {
        return *std::find_if(services.cbegin(), services.cend(), [iconType](const MenuServiceItem& msi) { return msi.iconType == iconType; });
    }
}
