#include "sendmessage.h"
#include <QJsonArray>

namespace InnertubeEndpoints
{
    SendMessage::SendMessage(const QJsonValue& data) : data(data) {}

    QJsonObject SendMessage::createBody(
        const InnertubeContext* context, const QJsonArray& textSegments,
        const QString& clientMessageId, const QString& params)
    {
        return {
            { "clientMessageId", clientMessageId },
            { "context", context->toJson() },
            { "params", params },
            { "richMessage", QJsonObject {
                { "textSegments", textSegments }
            }}
        };
    }

    QJsonObject SendMessage::createBody(
        const InnertubeContext* context, const QString& message,
        const QString& clientMessageId, const QString& params)
    {
        return createBody(context, QJsonArray { QJsonObject { { "text", message } } }, clientMessageId, params);
    }
}
