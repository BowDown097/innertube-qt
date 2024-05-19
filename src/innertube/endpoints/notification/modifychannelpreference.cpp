#include "modifychannelpreference.h"

namespace InnertubeEndpoints
{
    ModifyChannelPreference::ModifyChannelPreference(InnertubeContext* context, InnertubeAuthStore* authStore, const QString& params)
    {
        const QJsonValue data = get(context, authStore, QJsonObject {
            EndpointMethods::contextPair(context),
            { "params", params }
        });

        channelId = data["channelId"].toString();
        newNotificationButton = InnertubeObjects::NotificationPreferenceButton(
            data["newNotificationButton"]["subscriptionNotificationToggleButtonRenderer"]
        );
    }
}
