#include "getlivechat.h"
#include <QJsonDocument>

namespace InnertubeEndpoints
{
    GetLiveChat::GetLiveChat(const QString& continuation, InnertubeContext* context, InnertubeAuthStore* authStore)
    {
        const QJsonObject body {
            { "context", context->toJson() },
            { "continuation", continuation },
            { "webClientInfo", QJsonObject {
                { "isDocumentHidden", false }
            }}
        };

        QByteArray data = get("live_chat/get_live_chat", context, authStore, body);
        liveChatContinuation = QJsonDocument::fromJson(data)["continuationContents"]["liveChatContinuation"];
    }
}
