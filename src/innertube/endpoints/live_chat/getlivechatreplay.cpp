#include "getlivechatreplay.h"

namespace InnertubeEndpoints
{
    GetLiveChatReplay::GetLiveChatReplay(const QJsonValue& data)
        : liveChatContinuation(data["continuationContents"]["liveChatContinuation"]) {}

    QJsonObject GetLiveChatReplay::createBody(
        const InnertubeContext* context, const QString& continuationToken, const QString& playerOffsetMs)
    {
        return {
            { "context", context->toJson() },
            { "continuation", continuationToken },
            { "currentPlayerState", QJsonObject {
                { "playerOffsetMs", playerOffsetMs }
            }}
        };
    }
}
