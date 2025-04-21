#include "subscribe.h"
#include <QJsonArray>

namespace InnertubeEndpoints
{
    QJsonObject Subscribe::createBody(
        const InnertubeContext* context, const QStringList& channelIds, const QString& params)
    {
        return {
            { "channelIds", QJsonArray::fromStringList(channelIds) },
            { "context", context->toJson() },
            { "params", params }
        };
    }
}
