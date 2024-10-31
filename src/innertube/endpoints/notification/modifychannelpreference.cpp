#include "modifychannelpreference.h"

namespace InnertubeEndpoints
{
    ModifyChannelPreference::ModifyChannelPreference(const InnertubeContext* context, const InnertubeAuthStore* authStore,
                                                     const QString& params)
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
