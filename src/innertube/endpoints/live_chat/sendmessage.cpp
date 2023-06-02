#include "sendmessage.h"
#include <QJsonArray>

namespace InnertubeEndpoints
{
    SendMessage::SendMessage(const QString& message, InnertubeContext* context, InnertubeAuthStore* authStore, const QString& clientMessageId,
                             const QString& params)
    {
        QJsonObject body {
            { "clientMessageId", clientMessageId },
            { "context", context->toJson() },
            { "params", params },
            { "richMessage", QJsonObject {
                { "textSegments", QJsonArray {
                    QJsonObject {
                        { "text", message }
                    }
                }}
            }}
        };

        get("live_chat/send_message", context, authStore, body);
    }
}
