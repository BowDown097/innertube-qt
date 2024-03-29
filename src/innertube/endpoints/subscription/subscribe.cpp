#include "subscribe.h"
#include <QJsonArray>

namespace InnertubeEndpoints
{
    Subscribe::Subscribe(InnertubeContext* context, InnertubeAuthStore* authStore, const QStringList& channelIds,
                         const QString& params)
    {
        const QJsonObject body {
            { "channelIds", QJsonArray::fromStringList(channelIds) },
            { "context", context->toJson() },
            { "params", params }
        };
        get(context, authStore, body);
    }
}
