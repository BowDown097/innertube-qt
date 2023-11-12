#include "getlivechat.h"
#include <QJsonDocument>

namespace InnertubeEndpoints
{
    GetLiveChat::GetLiveChat(InnertubeContext* context, InnertubeAuthStore* authStore, const QString& continuation)
    {
        const QJsonObject body {
            { "context", context->toJson() },
            { "continuation", continuation },
            { "webClientInfo", QJsonObject {
                { "isDocumentHidden", false }
            }}
        };

        QByteArray data = get(context, authStore, body);
        liveChatContinuation = QJsonDocument::fromJson(data)["continuationContents"]["liveChatContinuation"];
    }
}
