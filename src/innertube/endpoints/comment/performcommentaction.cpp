#include "performcommentaction.h"

namespace InnertubeEndpoints
{
    PerformCommentAction::PerformCommentAction(const InnertubeContext* context, const InnertubeAuthStore* authStore,
                                               const QStringList& actions)
    {
        const QJsonValue data = get(context, authStore, QJsonObject {
            { "actions", QJsonArray::fromStringList(actions) },
            EndpointMethods::contextPair(context)
        });

        response.actionResults = data["actionResults"].toArray();
        response.actions = data["actions"].toArray();
    }
}
