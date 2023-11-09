#include "getlivechatreplay.h"
#include <QJsonDocument>

namespace InnertubeEndpoints
{
    GetLiveChatReplay::GetLiveChatReplay(const QString& continuation, InnertubeContext* context,
                                         InnertubeAuthStore* authStore, const QString& playerOffsetMs)
    {
        const QJsonObject body {
            { "context", context->toJson() },
            { "continuation", continuation },
            { "currentPlayerState", QJsonObject {
                { "playerOffsetMs", playerOffsetMs }
            }}
        };

        QByteArray data = get("live_chat/get_live_chat_replay", context, authStore, body);
        liveChatContinuation = QJsonDocument::fromJson(data)["continuationContents"]["liveChatContinuation"];
    }
}
