#include "subscribe.h"
#include <QJsonArray>

namespace InnertubeEndpoints
{
    Subscribe::Subscribe(const QStringList& channelIds, const QString& params, bool subscribing, InnertubeContext* context, CurlEasy* easy,
                         InnertubeAuthStore* authStore)
    {
        QJsonObject body {
            { "channelIds", QJsonArray::fromStringList(channelIds) },
            { "context", context->toJson() },
            { "params", params }
        };

        QByteArray data;
        get(subscribing ? "subscription/subscribe" : "subscription/unsubscribe", context, authStore, easy, body, data);
    }
}
