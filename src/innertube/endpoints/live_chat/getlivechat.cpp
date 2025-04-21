#include "getlivechat.h"

namespace InnertubeEndpoints
{
    GetLiveChat::GetLiveChat(const QJsonValue& data)
        : liveChatContinuation(data["continuationContents"]["liveChatContinuation"]) {}

    QJsonObject GetLiveChat::createBody(const InnertubeContext* context, const QString& continuationToken)
    {
        return {
            { "context", context->toJson() },
            { "continuation", continuationToken },
            { "webClientInfo", QJsonObject {
                { "isDocumentHidden", false }
            }}
        };
    }
}
