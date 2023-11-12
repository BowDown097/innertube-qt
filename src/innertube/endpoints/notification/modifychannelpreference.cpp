#include "modifychannelpreference.h"
#include <QJsonDocument>

namespace InnertubeEndpoints
{
    ModifyChannelPreference::ModifyChannelPreference(InnertubeContext* context, InnertubeAuthStore* authStore, const QString& params)
    {
        const QJsonObject body {
            { "context", context->toJson() },
            { "params", params }
        };

        QByteArray data = get(context, authStore, body);
        QJsonValue dataObj = QJsonDocument::fromJson(data).object();

        channelId = dataObj["channelId"].toString();
        newNotificationButton = InnertubeObjects::NotificationPreferenceButton(
            dataObj["newNotificationButton"]["subscriptionNotificationToggleButtonRenderer"]
        );
    }
}
