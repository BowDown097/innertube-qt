#include "modifychannelpreference.h"

namespace InnertubeEndpoints
{
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
