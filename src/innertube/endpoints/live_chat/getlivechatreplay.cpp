#include "getlivechatreplay.h"
#include <QJsonDocument>

namespace InnertubeEndpoints
{
    GetLiveChatReplay::GetLiveChatReplay(InnertubeContext* context, InnertubeAuthStore* authStore,
                                         const QString& continuation, const QString& playerOffsetMs)
    {
        const QJsonObject body {
            { "context", context->toJson() },
            { "continuation", continuation },
            { "currentPlayerState", QJsonObject {
                { "playerOffsetMs", playerOffsetMs }
            }}
        };

        QByteArray data = get(context, authStore, body);
        liveChatContinuation = QJsonDocument::fromJson(data)["continuationContents"]["liveChatContinuation"];
    }
}
