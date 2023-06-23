#include "sendmessage.h"

namespace InnertubeEndpoints
{
    SendMessage::SendMessage(const QJsonArray& textSegments, InnertubeContext* context, InnertubeAuthStore* authStore,
                             const QString& clientMessageId, const QString& params)
    {
        const QJsonObject body {
            { "clientMessageId", clientMessageId },
            { "context", context->toJson() },
            { "params", params },
            { "richMessage", QJsonObject {
                { "textSegments", textSegments }
            }}
        };
        get("live_chat/send_message", context, authStore, body);
    }

    SendMessage::SendMessage(const QString& message, InnertubeContext* context, InnertubeAuthStore* authStore,
                             const QString& clientMessageId, const QString& params)
        : SendMessage(QJsonArray { QJsonObject { { "text", message } } }, context, authStore, clientMessageId, params)
    {}
}
