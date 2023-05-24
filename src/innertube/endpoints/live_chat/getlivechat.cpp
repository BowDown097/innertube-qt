#include "getlivechat.h"
#include <QJsonArray>
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
        QJsonValue dataObj = QJsonDocument::fromJson(data).object();

        response.actionPanel = dataObj["continuationContents"]["liveChatContinuation"]["actionPanel"];
        response.actions = dataObj["continuationContents"]["liveChatContinuation"]["actions"].toArray();

        const QJsonArray continuationsJson = dataObj["continuationContents"]["liveChatContinuation"]["continuations"].toArray();
        for (const QJsonValue& v : continuationsJson)
            response.continuations.append(InnertubeObjects::InvalidationContinuation(v["invalidationContinuationData"]));
    }
}
