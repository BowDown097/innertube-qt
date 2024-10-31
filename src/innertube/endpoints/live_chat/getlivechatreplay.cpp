#include "getlivechatreplay.h"

namespace InnertubeEndpoints
{
    GetLiveChatReplay::GetLiveChatReplay(const InnertubeContext* context, const InnertubeAuthStore* authStore,
                                         const QString& continuation, const QString& playerOffsetMs)
    {
        const QJsonValue data = get(context, authStore, QJsonObject {
            EndpointMethods::contextPair(context),
            { "continuation", continuation },
            { "currentPlayerState", QJsonObject {
                { "playerOffsetMs", playerOffsetMs }
            }}
        });

        liveChatContinuation = data["continuationContents"]["liveChatContinuation"];
    }
}
