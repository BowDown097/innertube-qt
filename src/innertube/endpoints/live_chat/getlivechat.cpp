#include "getlivechat.h"

namespace InnertubeEndpoints
{
    GetLiveChat::GetLiveChat(const InnertubeContext* context, const InnertubeAuthStore* authStore, const QString& continuation)
    {
        const QJsonValue data = get(context, authStore, QJsonObject {
            EndpointMethods::contextPair(context),
            { "continuation", continuation },
            { "webClientInfo", QJsonObject {
                { "isDocumentHidden", false }
            }}
        });

        liveChatContinuation = data["continuationContents"]["liveChatContinuation"];
    }
}
