#include "subscribe.h"
#include <QJsonArray>

namespace InnertubeEndpoints
{
    Subscribe::Subscribe(const QStringList& channelIds, const QString& params, bool subscribing, InnertubeContext* context,
                         InnertubeAuthStore* authStore)
    {
        const QJsonObject body {
            { "channelIds", QJsonArray::fromStringList(channelIds) },
            { "context", context->toJson() },
            { "params", params }
        };
        get(subscribing ? "subscription/subscribe" : "subscription/unsubscribe", context, authStore, body);
    }
}
