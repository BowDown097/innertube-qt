#include "sendmessage.h"
#include <QJsonArray>

namespace InnertubeEndpoints
{
    SendMessage::SendMessage(const InnertubeContext* context, const InnertubeAuthStore* authStore,
                             const QJsonArray& textSegments, const QString& clientMessageId, const QString& params)
    {
        get(context, authStore, createBody(context, textSegments, clientMessageId, params));
    }

    SendMessage::SendMessage(const InnertubeContext* context, const InnertubeAuthStore* authStore,
                             const QString& message, const QString& clientMessageId, const QString& params)
        : SendMessage(context, authStore, QJsonArray { QJsonObject { { "text", message } } }, clientMessageId, params) {}

    QJsonObject SendMessage::createBody(const InnertubeContext* context, const QJsonArray& textSegments,
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
}
