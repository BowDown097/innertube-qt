#include "getlivechatreplay.h"

namespace InnertubeEndpoints
{
    GetLiveChatReplay::GetLiveChatReplay(const InnertubeContext* context, const InnertubeAuthStore* authStore,
                                         const QString& continuation, const QString& playerOffsetMs)
        : GetLiveChatReplay(get(context, authStore, createBody(context, continuation, playerOffsetMs))) {}

    GetLiveChatReplay::GetLiveChatReplay(const QJsonValue& data)
        : liveChatContinuation(data["continuationContents"]["liveChatContinuation"]) {}

    QJsonObject GetLiveChatReplay::createBody(const InnertubeContext* context, const QString& continuation,
                                              const QString& playerOffsetMs)
    {
        return {
            EndpointMethods::contextPair(context),
            { "continuation", continuation },
            { "currentPlayerState", QJsonObject {
                { "playerOffsetMs", playerOffsetMs }
            }}
        };
    }
}
