#include "modifychannelpreference.h"

namespace InnertubeEndpoints
{
    ModifyChannelPreference::ModifyChannelPreference(const InnertubeContext* context, const InnertubeAuthStore* authStore,
                                                     const QString& params)
        : ModifyChannelPreference(get(context, authStore, createBody(context, params))) {}

    ModifyChannelPreference::ModifyChannelPreference(const QJsonValue& data)
        : channelId(data["channelId"].toString()),
          newNotificationButton(data["newNotificationButton"]["subscriptionNotificationToggleButtonRenderer"]) {}

    QJsonObject ModifyChannelPreference::createBody(const InnertubeContext* context, const QString& params)
    {
        return {
            { "context", context->toJson() },
            { "params", params }
        };
    }
}
