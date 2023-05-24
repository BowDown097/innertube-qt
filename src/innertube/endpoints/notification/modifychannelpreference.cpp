#include "modifychannelpreference.h"

namespace InnertubeEndpoints
{
    ModifyChannelPreference::ModifyChannelPreference(const QString& params, InnertubeContext* context, InnertubeAuthStore* authStore)
    {
        const QJsonObject body {
            { "context", context->toJson() },
            { "params", params }
        };

        QByteArray data = get("notification/modify_channel_preference", context, authStore, body);
        QJsonValue dataObj = QJsonDocument::fromJson(data).object();

        channelId = dataObj["channelId"].toString();
        newNotificationButton = InnertubeObjects::NotificationPreferenceButton(
            dataObj["newNotificationButton"]["subscriptionNotificationToggleButtonRenderer"]
        );
    }
}
