#include "subscribe.h"
#include <QJsonArray>

namespace InnertubeEndpoints
{
    Subscribe::Subscribe(const InnertubeContext* context, const InnertubeAuthStore* authStore, const QStringList& channelIds,
                         const QString& params)
    {
        get(context, authStore, QJsonObject {
            { "channelIds", QJsonArray::fromStringList(channelIds) },
            EndpointMethods::contextPair(context),
            { "params", params }
        });
    }
}
