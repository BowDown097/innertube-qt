#include "getlivechat.h"

namespace InnertubeEndpoints
{
    GetLiveChat::GetLiveChat(const InnertubeContext* context, const InnertubeAuthStore* authStore, const QString& continuation)
        : GetLiveChat(get(context, authStore, createBody(context, continuation))) {}

    GetLiveChat::GetLiveChat(const QJsonValue& data)
        : liveChatContinuation(data["continuationContents"]["liveChatContinuation"]) {}

    QJsonObject GetLiveChat::createBody(const InnertubeContext* context, const QString& continuation)
    {
        return {
            { "context", context->toJson() },
            { "continuation", continuation },
            { "webClientInfo", QJsonObject {
                { "isDocumentHidden", false }
            }}
        };
    }
}
