#include "sendmessage.h"
#include <QJsonArray>

namespace InnertubeEndpoints
{
    SendMessage::SendMessage(const QJsonArray& textSegments, InnertubeContext* context, InnertubeAuthStore* authStore,
                             const QString& clientMessageId, const QString& params)
    {
        get(context, authStore, QJsonObject {
            { "clientMessageId", clientMessageId },
            EndpointMethods::contextPair(context),
            { "params", params },
            { "richMessage", QJsonObject {
                { "textSegments", textSegments }
            }}
        });
    }

    SendMessage::SendMessage(const QString& message, InnertubeContext* context, InnertubeAuthStore* authStore,
                             const QString& clientMessageId, const QString& params)
        : SendMessage(QJsonArray { QJsonObject { { "text", message } } }, context, authStore, clientMessageId, params) {}
}
