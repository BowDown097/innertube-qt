#include "unsubscribe.h"
#include <QJsonArray>

namespace InnertubeEndpoints
{
    Unsubscribe::Unsubscribe(const InnertubeContext* context, const InnertubeAuthStore* authStore,
                             const QStringList& channelIds, const QString& params)
    {
        get(context, authStore, QJsonObject {
            { "channelIds", QJsonArray::fromStringList(channelIds) },
            { "context", context->toJson() },
            { "params", params }
        });
    }
}
